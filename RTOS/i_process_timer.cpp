/**
This file implements the timer i-process.
**/

#include "i_process_timer.h"
#include "rtx.h"
#include <signal.h>
#include <string.h>

// Return the process tuple.
Process::ProcessTuple IProcessTimer::process()
{
	return ProcessTuple( I_PROCESS_TIMER, INVALID_PROCESS_PRIORITY, ( 1 << RSIGTIMER ) );
}

// Get the time delay specified by the message envelope. This function assumes that the message envelope data was written as an integer.
int IProcessTimer::get_envelope_time( MsgEnv * a )
{
	char *pAData = a->m_data;
	return *( ( int * ) pAData );
}

// Sorting algorithm for the m_waiting_time queue.
bool IProcessTimer::sort_timing_envelopes( MsgEnv * a, MsgEnv * b )
{
	return get_envelope_time( a ) <= get_envelope_time( b );
}

// Initialize the i-process timer. Set the sorting algorithm for the m_waiting_time priority queue.
IProcessTimer::IProcessTimer()
{
	m_waiting_time.set_sort( &sort_timing_envelopes );
}

void IProcessTimer::main()
{
	//update time
	Kernel::m_current_time++;

	// Check the inbox for new time delay requests.
	MsgEnv * time_envelope = Kernel::receive_message();
	while ( time_envelope != NULL )
	{
		// Add the message to the timer queue.
		rtx_stl::node<MsgEnv> * pNode = Kernel::request_message_node();
		pNode->set( time_envelope );
		m_waiting_time.enqueue( pNode );
		time_envelope = Kernel::receive_message();
	}
	
	// Check whether there are any messages in the timer queue which have expired.
	while ( !m_waiting_time.empty() && get_envelope_time( m_waiting_time.peek( 0 )->get() ) <= Kernel::m_current_time )
	{
		// Dequeue the message from the queue and send it to the process who requested the delay.
		rtx_stl::node<MsgEnv> * doneMessageNode = m_waiting_time.dequeue();
		MsgEnv * pDoneMessage = doneMessageNode->get();
		Kernel::release_message_node( doneMessageNode );
		PROCESS_ID destPID = pDoneMessage->get_source_pid();
		Kernel::send_message( destPID, pDoneMessage );
	}
}

void IProcessTimer::terminate()
{

}
