/**
Header file for the kernel.
**/

#ifndef KERNEL_H
#define KERNEL_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx_base.h"
#include "rtx_unix.h"
#include "stl_list.h"
#include "stl_pqueue.h"
#include "stl_queue.h"
#include "pcb.h"
#include "process.h"
#include "msgenv.h"
#include "tracebuf.h"
#include <setjmp.h>

class Kernel
{
private:
	
	static void signal_handler( int );

	static jmp_buf m_context;


	static bool sort_processes( UPCB *, UPCB * );
	static rtx_stl::pqueue <UPCB> m_ready_processes;

	// i-process list
	static rtx_stl::list <IPCB> m_i_processes;

	// message envelope manager
	static rtx_stl::queue<MsgEnv> m_available_envelopes;
	static rtx_stl::queue<MsgEnv> m_available_envelope_nodes;
	static rtx_stl::pqueue<UPCB> m_blocked_envelope_claim;
	static rtx_stl::list<UPCB> m_blocked_envelope_receive;
	static rtx_stl::queue<TraceBuffer> m_send_trace_buffers;
	static rtx_stl::queue<TraceBuffer> m_receive_trace_buffers;

	static rtx_stl::node<UPCB> * m_current_process;
	static rtx_stl::node<IPCB> * m_i_process_invoked;
	static bool m_handling_interrupt;

	static int m_atomic_count;
	static int m_signals_handled;
	static int m_current_signal_handled;

	static void UTIL_block_process( PROCESS_STATUS );
	static PCB * UTIL_find_process( PROCESS_ID, bool );
	static void UTIL_process_switch();
	static void UTIL_signal_handler( int );
	static UPCB * UTIL_get_user_process();
	static PCB * UTIL_get_current_process();
	static void UTIL_send_trace_buffer( MsgEnv * );
	static void UTIL_receive_trace_buffer( MsgEnv * );
	static void UTIL_write_trace_buffer( MsgEnv *, rtx_stl::queue<TraceBuffer> * );
	static rtx_stl::node<MsgEnv> * UTIL_request_message_node();
	static int UTIL_release_message_node( rtx_stl::node<MsgEnv> * pNode );

	// Helper process stuff.
	static buffer * m_keyboard_buffer;
	static int m_keyboard_file;

	static buffer * m_crt_buffer;
	static int m_crt_file;

	// Process IDs for the forked kernel processes running the helper processes.
	static int m_keyboard_helper_pid;
	static int m_crt_helper_pid;

protected:	
	static int m_current_time;
	
	static int register_process( Process * pProcess );

	// primitives
	static int send_message( PROCESS_ID dest_process_id, MsgEnv * msg_envelope );
	static MsgEnv * receive_message();
	static MsgEnv * request_msg_env();
	static int release_msg_env( MsgEnv * msg_env_ptr );
	static int release_processor();
	static int request_process_status( MsgEnv * msg_env_ptr );
	static int terminate();
	static int change_priority( PROCESS_PRIORITY new_priority, PROCESS_ID target_process_id );
	static int request_delay( int time_delay, MESSAGE_TYPE wakeup_code, MsgEnv * message_envelope );
	static int send_console_chars( MsgEnv * message_envelope );
	static int get_console_chars( MsgEnv * message_envelope );
	static int get_trace_buffers( MsgEnv * message_envelope );
	static rtx_stl::node<MsgEnv> * request_message_node();
	static int release_message_node( rtx_stl::node<MsgEnv> * pNode );

	static void atomic( bool );
	
public:
	static void init();
	static void run();
	
	friend class RTX;
	friend class IProcessTimer;
	friend class IProcessKeyboard;
	friend class IProcessCRT;
	friend class IProcessTerminate;
	friend struct TraceBuffer;
};

#endif
