/**
This file defines the api for the user processes to interact with the kernel. 
**/

#ifndef API_H
#define API_H
#ifdef _WIN32
#pragma once
#endif

#include "stl_node.h"
#include "rtx_base.h"
#include "msgenv.h"
 
class RTX 
{ 
public:

	// User process primitives
	static int register_process( Process * process );
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
	static int get_console_chars(MsgEnv * message_envelope );
	static int get_trace_buffers( MsgEnv * message_envelope);

	// Additional primitives. These primitives are needed for the stl structures.
	static rtx_stl::node<MsgEnv> * request_message_node();
	static int release_message_node( rtx_stl::node<MsgEnv> * pNode );
};

#endif
