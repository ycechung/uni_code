// Kernel functions.
//
// Doug 11/5/2010
//	Here is my explanation to James on why we had to do a few hacks here:
//
//I have a kernel run function which basically tells it "everything has been initialized, do your thing"
//that's all fine and dandy but
//as part of it, it does a bunch of function calls to the processes to set up their context
//when it saves their context, it screws up the calling function's stack even though it's technically getting restored
//so we lose all of our kernel variables coming back
//so I solved that problem by creating a new function outside of the scope of the kernel
//which the kernel then calls to do all the jumping for it
//but the problem is that if you pass it any polymorphic classes (such as our process system) they get screwed up as well
//so I had to make a global process pointer which I set first
//then call the isolated jump function
//so the isolated jump refers to the global process pointer for each process entry point

#include <stdio.h>
#include <stdlib.h>

#include "rtx.h"
#include "kernel.h"
#include "tracebuf.h"

#include "memory.h"
#include <time.h>
#include <setjmp.h>

#ifndef _WIN32
#include <signal.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#endif

// Doug 11/20/2010
//	Made everything static. This was done because there is no reason that one would
//	want to have more than one instance of the kernel, anyway. there were some
//	problems regarding context being lost, so I decided to play it safe and just
//	make sure everything was effectively treated as a global.
rtx_stl::pqueue<UPCB> Kernel::m_ready_processes;
rtx_stl::list<IPCB> Kernel::m_i_processes;
rtx_stl::queue<MsgEnv> Kernel::m_available_envelopes;
rtx_stl::queue<MsgEnv> Kernel::m_available_envelope_nodes;
rtx_stl::pqueue<UPCB> Kernel::m_blocked_envelope_claim;
rtx_stl::list<UPCB> Kernel::m_blocked_envelope_receive;
rtx_stl::queue<TraceBuffer> Kernel::m_send_trace_buffers;
rtx_stl::queue<TraceBuffer> Kernel::m_receive_trace_buffers;
rtx_stl::node<IPCB> * Kernel::m_i_process_invoked;
rtx_stl::node<UPCB> * Kernel::m_current_process;
int Kernel::m_signals_handled;
int Kernel::m_current_signal_handled;
jmp_buf Kernel::m_context;
int Kernel::m_current_time;
int Kernel::m_atomic_count;
bool Kernel::m_handling_interrupt;

// Helper process stuff.
buffer * Kernel::m_keyboard_buffer;
buffer * Kernel::m_crt_buffer;
int Kernel::m_keyboard_helper_pid;
int Kernel::m_crt_helper_pid;
int Kernel::m_keyboard_file;
int Kernel::m_crt_file;

using namespace rtx_stl;

// Doug 11/5/2010
//	The Process pointer below here and isolated_jump() functions are total
//	hacks that I had to use because setjmp() and longjmp() don't operate
//  the way one would expect. See the top header for my explanation to James.
Process * g_pProcess;
void isolated_jump( char * stack, jmp_buf * kernel_buf, jmp_buf * proc_buf )
{
	// Save the current context so that the stack pointer can be restored
	// after the assembly instruction.
	if ( setjmp( *kernel_buf ) == 0 )
	{
		// Change the stack pointer to the process's stack, so it can be
		// saved in the next setjmp() call.
#ifndef _WIN32
		__asm__ ( "movl %0,%%esp":"=m" ( stack ) );
#endif
		if ( setjmp( *proc_buf ) == 0 )
		{
			// Jump back to the previous context.
			longjmp( *kernel_buf, 1 );
		}
		else
		{
			// Virtual function call to the process' main function. This
			// effectively starts the process for the first time.
			g_pProcess->main();
	  	}
	}
}

// Doug 11/5/2010
//	Signals are not context-safe, so we have to specifically tell it to call the
//	kernel's utility function for handling it. Notice that the signal_handler()
//	function below is static.
// Doug 11/25/2010
//	This is no longer necessary since everything has been ported to static, but
//	I'm leaving it like this anyway.
void Kernel::signal_handler( int signal )
{
	Kernel::UTIL_signal_handler( signal );
}

void Kernel::UTIL_signal_handler( int sig )
{
	// Inform I-Processes of what signal they are currently handling, in case
	// they handle multiple signals.
	m_current_signal_handled = sig;

	// Find the I-Process that handles this signal and execute it. Note that
	// if the same signal is registered multiple times by different processes,
	// it will get handled by each.
	bool found = false;
	for ( int i = 0; i < m_i_processes.size(); i++ )
	{
		// Check if a bit shifted version of this signal number is contained
		// within this process's signals handled.
		if ( m_i_processes.get( i )->get()->m_signals_handled & ( 1 << sig ) )
		{
			found = true;

			m_handling_interrupt = false;
			m_i_process_invoked = m_i_processes.get( i );
			UTIL_process_switch();
		}
	}

#ifndef _WIN32
	signal( sig, &signal_handler );
#endif

	assert( found );
}

// Doug 11/25/2010
//	A lot of this stuff is unnecessary since the members are
//	static, but I figure it's a good idea to leave like this
//	since any useless code will probably get optimized out,
//	and if init() was ever needed to reset all variables,
//	we can use it.
void Kernel::init()
{
	m_ready_processes.set_sort( &sort_processes );
	m_blocked_envelope_claim.set_sort( &sort_processes );

	for ( int i = 0; i < ENVELOPE_NUM; i++ )
	{
		node <MsgEnv> * pNode = new node<MsgEnv>;
		pNode->set( new MsgEnv );
		m_available_envelopes.enqueue( pNode );
	}

	for ( int i = 0; i < TRACE_NUM; i++ )
	{
		node <TraceBuffer> * pNode = new node<TraceBuffer>;
		pNode->set( new TraceBuffer );
		m_send_trace_buffers.enqueue( pNode );

		pNode = new node<TraceBuffer>;
		pNode->set( new TraceBuffer );
		m_receive_trace_buffers.enqueue( pNode );
	}

	m_atomic_count = 0;

	m_signals_handled = 0;

	m_i_process_invoked = NULL;
	m_current_process = NULL;
	m_handling_interrupt = false;

	m_current_time = 0;
}

void Kernel::run()
{
	// Iterate through all ready processes and get them prepared for being
	// run the first time.
	for ( int i = 0 ; i < m_ready_processes.size(); i++ )
	{
		node <UPCB> * pNode = m_ready_processes.peek( i );

		m_current_process = pNode;

		// Hack in the global so it doesn't get overwritten.
		g_pProcess = pNode->get()->m_model;
		isolated_jump( pNode->get()->m_stack, &m_context, &pNode->get()->m_context );
	}

	// Iterate through all I-Processes and set up signals for handling.
	for ( int i = 0; i < m_i_processes.size(); i++ )
	{
		node<IPCB> * pNode = m_i_processes.get( i );

		// All signals handled are cached in here for quick access.
		// This is done so that iteration is not necessary for simple
		// tasks.
		m_signals_handled |= pNode->get()->m_signals_handled;

		// Doug 11/25/2010
		//	Special case. The SIGALRM (RSIGTIMER as of writing) is not
		//	called unless we set a timer. The second parameter is the
		//	interval.
#ifndef _WIN32
		if ( pNode->get()->m_signals_handled & ( 1 << RSIGTIMER ) )
			ualarm( 100000, 100000 );
#endif
	}

	// Use the POSIX call to hook the signals.
#ifndef _WIN32
	for ( int i = 0; i < 32; i++ )
		if ( m_signals_handled & ( 1 << i ) )
			signal( i, &signal_handler );
#endif

#ifndef _WIN32
	// Get the pid of the RTX for passing to the helper processes.
	int rtx_pid = getpid();

	// Create the buffer file for the keyboard.
	m_keyboard_file = open( KEYBOARD_FILENAME, O_RDWR | O_CREAT , ( mode_t ) 0755 );

	// Truncate the file to the correct size (got bus errors without this line).
	ftruncate( m_keyboard_file, sizeof( buffer ) );

	// Get a pointer to the shared memory.
	m_keyboard_buffer = ( buffer * ) mmap( NULL, sizeof( buffer ), PROT_READ | PROT_WRITE, MAP_SHARED, m_keyboard_file, ( off_t ) 0 );

	// Fork the keyboard helper process.
	m_keyboard_helper_pid = fork();
	if ( m_keyboard_helper_pid == 0 )
	{
		// Format the parameters to pass to the helper process.
		char file_id_buffer[32];
		char rtx_pid_buffer[32];

		sprintf( file_id_buffer, "%d", m_keyboard_file );
		sprintf( rtx_pid_buffer, "%d", rtx_pid );

		// Load the keyboard process into the forked process.
		execl( "./kbd", "./kbd", file_id_buffer, rtx_pid_buffer, NULL );

		// This should never be reached.
		printf( "an error occurred with the keyboard helper process\n" );
		terminate();
	}
	else
	{
		// Give the helper processes time to start.
		sleep(3);
	}

	// Create a buffer file for the crt
	m_crt_file = open( CRT_FILENAME, O_RDWR | O_CREAT, ( mode_t ) 0755 );

	// Truncate the file to the correct sie (got bus errors without this line).
	ftruncate( m_crt_file, sizeof( buffer ) );

	// Map the shared memory and store the location to it.
	m_crt_buffer = ( buffer * ) mmap( NULL, sizeof( buffer ), PROT_READ | PROT_WRITE, MAP_SHARED, m_crt_file, ( off_t ) 0 );

	// Fork the crt helper process.
	m_crt_helper_pid = fork();
	if ( m_crt_helper_pid == 0 )
	{
		// Format the parameters to pass to the helper process.
		char file_id_buffer[32];
		char rtx_pid_buffer[32];

		sprintf( file_id_buffer, "%d", m_crt_file );
		sprintf( rtx_pid_buffer, "%d", rtx_pid );

		// Load the CRT process into the forked process.
		execl( "./crt", "./crt", file_id_buffer, rtx_pid_buffer, NULL );

		// This should never be executed.
		printf("an error occurrred with the crt helper process\n");
		terminate();
	}
	else
	{
		// Give the helper process time to start.
		sleep(3);
	}

#endif

	// Doug 11/25/2010
	//	Indicate completion of the initialization and switch to the highest priority process.
	//	The global initialization value is used so that we can block calls to the new()
	//	operator after this point. Check memory.h and memory.cpp for more details.
	gInitialized = true;
	UTIL_process_switch();
}

void Kernel::atomic( bool setting )
{
	m_atomic_count += setting ? 1 : -1;

#ifndef _WIN32
	sigset_t current, next;
	if ( setting )
	{
		sigemptyset( &next );

		// Iterate through all handled signals and mask them.
		for ( int i = 0; i < 32; i++ )
		{
			if ( !( m_signals_handled & ( 1 << i ) ) )
				continue;

			sigaddset( &next, i );
		}

		sigprocmask( SIG_BLOCK, &next, &current );
	}
	else if ( m_atomic_count <= 0 )
	{
		// Doug 11/25/2010
		//	Unblock all blocked signals. This only affects this
		//	process, and since we don't want anything masked when
		//	atomic is off, we don't have to do the weird static
		//	caching thing that is done in the example code. I have
		//	tested this and verified that it works fine. Also note
		//	that making it static throws off the branch prediction,
		//	so this is probably a lot faster.
		sigfillset( &next );
		sigprocmask( SIG_UNBLOCK, &next, NULL );
		// In case it went lower.
		m_atomic_count = 0;
	}
#endif
}

bool Kernel::sort_processes( UPCB * a, UPCB * b )
{
	return b->m_priority >= a->m_priority;
}

void Kernel::UTIL_process_switch()
{
	// Check if the interrupt isn't already being handled. If it is, switch
	// to a user process instead.
	if ( m_i_process_invoked != NULL && !m_handling_interrupt )
	{
		m_handling_interrupt = true;

		m_current_process->get()->m_status = INTERRUPTED;

		// Doug 11/25/2010
		//	Turn on atomic operation so that it doesn't get interrupted.
		//	This should never matter since signals cannot be invoked while
		//	another signal is being handled.
		atomic( true );
		m_i_process_invoked->get()->m_model->main();
		atomic( false );

		// Go back to the previous state, before the interrupt was handled.
		m_current_process->get()->m_status = EXECUTING;
		m_i_process_invoked = NULL;
	}
	else
	{
		// Stop the i-process if it was previously invoked.
		m_handling_interrupt = false;
		m_i_process_invoked = NULL;

		node<UPCB> * pUPCB = m_ready_processes.dequeue();
		pUPCB->get()->m_status = EXECUTING;

		m_current_process = pUPCB;

		// Write to the global process variable so that, if this the first
		// time it's being called, it won't break.
		g_pProcess = pUPCB->get()->m_model;

		// Turn off atomic operation. If it was already off, this will just
		// be ignored.
		m_atomic_count = 0;
		atomic( false );

		// Jump to the process context.
		longjmp( pUPCB->get()->m_context, 1 );
	}
}

// Doug 11/25/2010
//	These are just wrappers for the UTIL_write_trace_buffer() function. All
//	they do is pass a specific queue of trace buffers to it.
void Kernel::UTIL_send_trace_buffer( MsgEnv * pMsgEnv )
{
	UTIL_write_trace_buffer( pMsgEnv, &m_send_trace_buffers );
}

void Kernel::UTIL_receive_trace_buffer( MsgEnv * pMsgEnv )
{
	UTIL_write_trace_buffer( pMsgEnv, &m_receive_trace_buffers );
}

void Kernel::UTIL_write_trace_buffer( MsgEnv * pMsgEnv, queue<TraceBuffer> * pTraceBuffers )
{
	// Grab a trace buffer and push it to the back of the queue.
	node<TraceBuffer> * pNode = pTraceBuffers->dequeue();
	pNode->get()->destination_id = pMsgEnv->m_destination_pid;
	pNode->get()->source_id = pMsgEnv->m_source_pid;
	pNode->get()->time_stamp = m_current_time;
	pNode->get()->message_type = pMsgEnv->m_message_type;
	pTraceBuffers->enqueue( pNode );
}

// Finds a process somewhere in one of the kernel structures. The second parameter
// specifies whether or not the process must be a user process. This allows safe
// casting to a UPCB without using RTTI.
PCB * Kernel::UTIL_find_process( PROCESS_ID id, bool user = false )
{
	if ( m_current_process->get()->m_id == id )
		return m_current_process->get();

	if ( !user && m_i_process_invoked != NULL && m_i_process_invoked->get()->m_id == id )
		return m_i_process_invoked->get();

	for ( int i = 0; i < m_ready_processes.size(); i++ )
		if ( ( m_ready_processes.peek( i )->get() )->m_id == id )
			return m_ready_processes.peek( i )->get();

	if ( !user )
		for ( int i = 0; i < m_i_processes.size(); i++ )
			if ( ( m_i_processes.get( i )->get() )->m_id == id )
				return m_i_processes.get( i )->get();

	for ( int i = 0; i < m_blocked_envelope_claim.size(); i++ )
		if ( ( m_blocked_envelope_claim.peek( i )->get() )->m_id == id )
			return m_blocked_envelope_claim.peek( i )->get();

	for ( int i = 0; i < m_blocked_envelope_receive.size(); i++ )
		if ( ( m_blocked_envelope_receive.get( i )->get() )->m_id == id )
			return m_blocked_envelope_receive.get( i )->get();

	return NULL;
}

// Gets the user process if it is currently running. Note that, if an I-Process
// is being handled, it will return NULL.
UPCB * Kernel::UTIL_get_user_process()
{
	return m_i_process_invoked == NULL ? m_current_process->get() : NULL;
}

// Returns the current running process, regardless of what type it is.
PCB * Kernel::UTIL_get_current_process()
{
	return m_i_process_invoked == NULL ? ( PCB * )( m_current_process->get() ) : ( PCB * )( m_i_process_invoked->get() );
}

// Blocks a process and process switches to a different process.
void Kernel::UTIL_block_process( PROCESS_STATUS status )
{
	// If the current process isn't a user process, don't block it.
	UPCB * pUProcess = UTIL_get_user_process();
	if ( pUProcess == NULL )
		return;

	// Block the process and choose another process to execute.
	pUProcess->m_status = status;
	switch ( status )
	{
	case BLOCK_ENV_RECEIVE:
		m_blocked_envelope_receive.push_back( m_current_process );
		break;
	case BLOCK_ENV_CLAIM:
		m_blocked_envelope_claim.enqueue( m_current_process );
		break;
	default:
		assert( false );
		break;
	}

	if ( setjmp( m_current_process->get()->m_context ) == 0 )
		UTIL_process_switch();
}

// Doug 11/25/2010
//	Gets a node for a message envelope. As of writing, this is only
//	necessary for Process C. There is no protection on this because
//	it is assumed that, if it has a message envelope, there must be
//	a matching node. Instead of blocking, it just fails. This is a
//	better design decision since waiting for a node to become
//	available allows horrible code to keep running (depending on
//	a node that is not matched with a message envelope).
node<MsgEnv> * Kernel::UTIL_request_message_node()
{
	if ( m_available_envelope_nodes.empty() )
		return NULL;

	return m_available_envelope_nodes.dequeue();
}

int Kernel::UTIL_release_message_node( node<MsgEnv> * pNode )
{
	// We NULL this so that, when freed up, it doesn't try to destroy
	// an object that doesn't exist anymore, or is referenced elsewhere.
	pNode->set( NULL );
	m_available_envelope_nodes.enqueue( pNode );
	return 1;
}

// Doug 11/25/2010
//	Registers a process with the kernel so that it can be handled properly.
//	This is wrapped in the PROCESS_REGISTER() macro, which is run in main.cpp.
//	A Process polymorphic class is passed in, and since it is an abstract class,
//	the vtables resolve such that any virtual function calls get passed along
//	to the derived class.
//	I-Processes are registered by having the tuple return a non-zero signals_handled
//	member, and U-Processes are registered by having the tuple return a zero
//	signals_handled member.
int Kernel::register_process( Process * pProcess )
{
	Process::ProcessTuple tuple = pProcess->process();

	// Out of range.
	if ( tuple.id < 0 || tuple.id >= PROCESS_ID_SIZE )
		return 0;

	if ( tuple.priority < 0 || tuple.priority >= PROCESS_PRIORITY_SIZE )
		return 0;

	node<PCB> * pNode = new node<PCB>;
	PCB * pPCB;

	if ( tuple.signals_handled == 0 )
	{
		UPCB * pUPCB = new UPCB( pProcess );
		pPCB = ( PCB * ) pUPCB;

		pNode->set( pUPCB );
		m_ready_processes.enqueue( ( node<UPCB> * ) pNode );
	}
	else
	{
		IPCB * pIPCB = new IPCB( pProcess );
		pPCB = ( PCB * ) pIPCB;

		pNode->set( pIPCB );
		m_i_processes.push_back( ( node<IPCB> * ) pNode );
	}

	return 1;
}

// Doug 11/25/2010
//	Wrappers for the UTIL functions. These were initially written because we
//	planned on blocking processes that request a node when there are none
//	available, but we decided against this.
node<MsgEnv> * Kernel::request_message_node()
{
	return UTIL_request_message_node();
}

int Kernel::release_message_node( node<MsgEnv> * pNode )
{
	return UTIL_release_message_node( pNode );
}

int Kernel::send_message( PROCESS_ID dest_process_id, MsgEnv * msg_envelope )
{
	// Write the source ID.
	msg_envelope->m_source_pid = UTIL_get_current_process()->m_id;

	msg_envelope->m_destination_pid = dest_process_id;

	// Get the destination PCB.
	PCB * pDestination = UTIL_find_process( dest_process_id );
	if ( pDestination == NULL )
		return 0;

	// Package the envelope into a node, so that it can be placed into
	// an STL structure.
	node<MsgEnv> * pMessage = UTIL_request_message_node();
	pMessage->set( msg_envelope );

	// Add the message to the destination PCB's message queue.
	pDestination->m_envelope_inbox.enqueue( pMessage );

	// Check if the process was blocked, and if so, remove it
	// and mark it as ready to run. Note that this may look
	// like it can be optimized by first checking the process'
	// status flag, but we can't since it's not guaranteed to be
	// a user process.
	for ( int i = 0; i < m_blocked_envelope_receive.size(); i++ )
	{
		if ( m_blocked_envelope_receive.get( i )->get()->m_id == dest_process_id )
		{
			node<UPCB> * pNode = m_blocked_envelope_receive.remove( i );
			pNode->get()->m_status = READY;
			m_ready_processes.enqueue( pNode );
			break;
		}
	}

	// Write to the trace buffers that this happened.
	UTIL_send_trace_buffer( msg_envelope );

	return 1;
}

MsgEnv * Kernel::receive_message()
{
	node<MsgEnv> * pEmptyNode;

	// Returns NULL if an I-Process receives a message when there are none
	// waiting for it. Blocks U-Processes instead.
	if ( m_i_process_invoked != NULL )
	{
		if ( m_i_process_invoked->get()->m_envelope_inbox.empty() )
			return NULL;

		pEmptyNode = m_i_process_invoked->get()->m_envelope_inbox.dequeue();
	}
	else
	{
		if ( m_current_process->get()->m_envelope_inbox.empty() )
			UTIL_block_process( BLOCK_ENV_RECEIVE );

		pEmptyNode = m_current_process->get()->m_envelope_inbox.dequeue();
	}

	// Remove the first message in the process' message queue and release
	// the node that it was stored in.
	MsgEnv * message = pEmptyNode->get();
	UTIL_release_message_node( pEmptyNode );

	UTIL_receive_trace_buffer( message );

	return message;
}

MsgEnv * Kernel::request_msg_env()
{
	// Returns NULL if an I-Process requests a message when there are none
	// available. Blocks U-Processes instead.
	if ( m_available_envelopes.empty() )
	{
		if ( m_i_process_invoked != NULL )
			return NULL;
		else
			UTIL_block_process( BLOCK_ENV_CLAIM );
	}

	// Get an available envelope and release the node that it was stored in.
	node<MsgEnv> * pNode = m_available_envelopes.dequeue();
	MsgEnv * pMsgEnv = pNode->get();
	UTIL_release_message_node( pNode );

	return pMsgEnv;
}

int Kernel::release_msg_env( MsgEnv * msg_env_ptr )
{
	// Put the message envelope in a node so that it can be stored in an
	// STL structure.
	node<MsgEnv> * pEmptyNode = UTIL_request_message_node();
	pEmptyNode->set( msg_env_ptr );
	m_available_envelopes.enqueue( pEmptyNode );

	// If there was a process waiting for an envelope to become available,
	// unblock it and mark it as ready to execute.
	if ( !m_blocked_envelope_claim.empty() )
	{
		node <UPCB> * pNode = m_blocked_envelope_claim.dequeue();
		pNode->get()->m_status = READY;
		m_ready_processes.enqueue( pNode );
	}

	return 1;
}

int Kernel::release_processor()
{
	// Does nothing if invoked by an I-Process.
	UPCB * pUPCB;
	if ( m_current_process != NULL && ( pUPCB = UTIL_get_user_process() ) != NULL )
	{
		// Change its status from EXECUTING to READY and put it in the ready queue.
		pUPCB->m_status = READY;
		m_ready_processes.enqueue( m_current_process );

		if ( setjmp( m_current_process->get()->m_context ) == 0 )
			UTIL_process_switch();
	}

	return 1;
}

// Writes the Process::StatusTuple structure for each process directly into the envelope's
// data field. Note that this is a status tuple itself, not a string representation of it
// or anything like that.
int Kernel::request_process_status( MsgEnv * msg_env_ptr )
{
	byte * data = &msg_env_ptr->m_data[1];

	// Write the current process' data to the first open spot.
	// Doug 11/8/2010
	//	NOTE FOR TA's:
	//	In case you don't know, this is the placement new operation. It uses an already
	//	allocated block of memory and calls the constructor for an object on it. WE ARE
	//	NOT CREATING OR ALLOCATING NEW MEMORY HERE.
	//	Also, you're probably thinking that this leaks memory since we never call the
	//	destructor. It won't; the reason being that StatusTuple follows ANSI C conventions
	//	and is, for all intents and purposes, a "Plain Old C" structure. RAII does not
	//	actually apply here.
	new ( data ) Process::StatusTuple( m_current_process->get()->m_id, m_current_process->get()->m_priority, m_current_process->get()->m_status );
	int i = 1;

	for ( int index = 0; index < m_ready_processes.size() && ( i + 1 ) * sizeof( Process::StatusTuple ) < sizeof( MsgEnv ); index++ )
	{
		UPCB * pUPCB = m_ready_processes.peek( index )->get();

		new ( &data[i++ * sizeof( Process::StatusTuple )] ) Process::StatusTuple( pUPCB->m_id, pUPCB->m_priority, pUPCB->m_status );
	}
	for ( int index = 0; index < m_blocked_envelope_claim.size() && ( i + 1 ) * sizeof( Process::StatusTuple ) < sizeof( MsgEnv ); index++ )
	{
		UPCB * pUPCB = m_blocked_envelope_claim.peek( index )->get();
		new ( &data[i++ * sizeof( Process::StatusTuple )] ) Process::StatusTuple( pUPCB->m_id, pUPCB->m_priority, pUPCB->m_status );
	}
	for ( int index = 0; index < m_blocked_envelope_receive.size() && ( i + 1 ) * sizeof( Process::StatusTuple ) < sizeof( MsgEnv ); index++ )
	{
		UPCB * pUPCB = m_blocked_envelope_receive.get( index )->get();
		new ( &data[i++ * sizeof( Process::StatusTuple )] ) Process::StatusTuple( pUPCB->m_id, pUPCB->m_priority, pUPCB->m_status );
	}


	msg_env_ptr->m_data[0] = ( char ) i;

	msg_env_ptr->m_message_type = ALL_PROCESS;

	return 1;
}

int Kernel::terminate()
{
	// Doug 11/25/2010
	//	Clear all memory, even though it will get destroyed on exit anyway.
	//	This is done because the project requirements are arbitrary, vague
	//	and often conflicting, so I figured it's better to be safe than
	//	sorry. The nodes also free whatever content is inside them, which
	//	you can see in the STL headers. That way, we don't need crazy/retardedly
	//	long code here to iterate through everything and destroy each and every
	//	block of memory manually.
	m_i_processes.clear();
	m_ready_processes.clear();
	m_blocked_envelope_claim.clear();
	m_blocked_envelope_receive.clear();

	m_available_envelopes.clear();
	m_available_envelope_nodes.clear();

	m_send_trace_buffers.clear();
	m_receive_trace_buffers.clear();

	delete m_current_process;

#ifndef _WIN32
	// Terminate the helper processes.
    kill( m_keyboard_helper_pid, SIGINT );
    kill( m_crt_helper_pid, SIGINT );

    // Unlink pointers to the shared memory.
    if ( munmap( ( void * ) m_keyboard_buffer, sizeof( buffer ) ) != 0 )
            printf( "Unmapping keyboard shared memory failed.\n" );
    if ( munmap( ( void * ) m_crt_buffer, sizeof( buffer ) ) != 0 )
            printf( "Unmapping crt shared memory failed.\n" );

    // Close shared memory files.
    if ( close( m_keyboard_file ) != 0 )
            printf( "Closing keyboard shared memory file failed.\n" );
    if ( close( m_crt_file ) != 0)
            printf( "Closing CRT shared memory file failed.\n" );

    // Delete the shared memory files.
    if ( unlink( KEYBOARD_FILENAME ) != 0 )
            printf( "Deleting keyboard shared memory file failed.\n" );
    if ( unlink( CRT_FILENAME ) != 0 )
            printf( "Deleting CRT shared memory file failed.\n" );
#endif

	exit( 0 );

	return 1;
}

// Changes the priority of a user process with some checks on parameters passed.
int Kernel::change_priority( PROCESS_PRIORITY new_priority, PROCESS_ID target_process_id )
{
	// Out of range and invalid checks.
	if ( target_process_id < 0 || target_process_id >= PROCESS_ID_SIZE || target_process_id == PROCESS_NULL )
		return 0;

	if ( new_priority < 0 || new_priority >= PROCESS_PRIORITY_SIZE )
		return 0;

	// Find the PCB of the process ID passed.
	PCB * pPCB = UTIL_find_process( target_process_id, true );
	if ( pPCB == NULL )
		return 0;

	// Must succeed, and I don't like depending on RTTI.
	UPCB * pUPCB = static_cast<UPCB *>( pPCB );
	pUPCB->m_priority = new_priority;

	// If it was in the process queue, force a re-sort.
	// This is a slow operation, but is only invoked once in a while
	// and is a small price to pay for the much better abstraction
	// that this model gives.
	if ( pUPCB->m_id != m_current_process->get()->m_id )
	{
		// Store the entire queue in a temporary queue, then copy it
		// back to the m_ready_processes priority queue so that it
		// gets sorted again.
		queue<UPCB> ready_processes;
		while ( !m_ready_processes.empty() )
			ready_processes.enqueue( m_ready_processes.dequeue() );
		while ( !ready_processes.empty() )
			m_ready_processes.enqueue( ready_processes.dequeue() );
	}

	return 1;
}

// Requests a delay, but does not block the process. It must call receive_message() after it and
// wait for the DISPLAY_ACK message type before it can be considered awoken.
int Kernel::request_delay( int time_delay, MESSAGE_TYPE wakeup_code, MsgEnv * message_envelope )
{
	message_envelope->m_message_type = wakeup_code;

	// Write the time delay, using the first 4 bytes of the envelope's data section instead of
	// just the first byte (character).
	char * pData = message_envelope->m_data;
	*( ( int * ) pData ) = m_current_time + time_delay;

	// Send the message to the timer I-Process.
	send_message( I_PROCESS_TIMER, message_envelope );

	return 1;
}

// Wrapper for send_message to the CRT I-Process, with an immediate invocation.
int Kernel::send_console_chars( MsgEnv * message_envelope )
{
	int returnValue = send_message( I_PROCESS_CRT, message_envelope );
	// Immediately invoke the CRT in read mode.
	signal_handler( RSIGCRTR );
	return returnValue;
}

// Wrapper for send_message to the keyboard I-Process.
int Kernel::get_console_chars( MsgEnv * message_envelope )
{
	return send_message( I_PROCESS_KEYBOARD, message_envelope );
}

// Writes the TraceBuffer structure for each trace buffer directly into the envelope's
// data field. Note that this is a trace buffer itself, not a string representation of it
// or anything like that.
int Kernel::get_trace_buffers( MsgEnv * message_envelope )
{
	// Store the amount of trace buffers into the first two bytes.
	message_envelope->m_data[0] = ( char ) m_send_trace_buffers.size();
	message_envelope->m_data[1] = ( char ) m_receive_trace_buffers.size();

	byte * data = &message_envelope->m_data[2];
	int i = 0;
	for ( int index = m_send_trace_buffers.size() - 1; index >= 0 && ( i + 1 ) * sizeof( TraceBuffer ) < sizeof( MsgEnv ); index-- )
	{
		TraceBuffer * pTraceBuffer = m_send_trace_buffers.peek( index )->get();

		// Doug 11/8/2010
		//	NOTE FOR TA's:
		//	In case you don't know, this is the placement new operation. It uses an already
		//	allocated block of memory and calls the constructor for an object on it. WE ARE
		//	NOT CREATING OR ALLOCATING NEW MEMORY HERE.
		//	Also,  you're probably thinking that this leaks memory since we never call the
		//	destructor. It won't; the reason being that TraceBuffer follows ANSI C conventions
		//	and is, for all intents and purposes, a C structure.
		new ( &data[i++ * sizeof( TraceBuffer )] ) TraceBuffer( pTraceBuffer->destination_id, pTraceBuffer->source_id, pTraceBuffer->time_stamp, pTraceBuffer->message_type );
	}

	for ( int index = m_receive_trace_buffers.size() - 1; index >= 0 && ( i + 1 ) * sizeof( TraceBuffer ) < sizeof( MsgEnv ); index-- )
	{
		TraceBuffer * pTraceBuffer = m_receive_trace_buffers.peek( index )->get();
		new ( &data[i++ * sizeof( TraceBuffer )] ) TraceBuffer( pTraceBuffer->destination_id, pTraceBuffer->source_id, pTraceBuffer->time_stamp, pTraceBuffer->message_type );
	}

	message_envelope->m_message_type = TRACE_BUFFER;

	return 1;
}
