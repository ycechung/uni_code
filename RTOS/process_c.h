/**
Header file for process c.
**/

#ifndef PROCESS_C_H
#define PROCESS_C_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx.h"

class ProcessC : private Process
{
	PROCESS_DECLARE()
	
	// Holds messages which were received from the inbox but not yet handled.
	rtx_stl::queue<MsgEnv> m_local_messages;

	// Add a message to the local message queue.
	int enqueue_local_message( MsgEnv * message );

	// Get a message from the local message queue.
	MsgEnv * dequeue_local_message();
};

#endif
