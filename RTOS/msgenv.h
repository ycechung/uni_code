/**
Header file for the message envelope.
**/

#ifndef MSG_ENV_H
#define MSG_ENV_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx_base.h"

class MsgEnv
{
	WATCH_INITIALIZATION( MsgEnv );

protected:
	
	// Type of the message.
	MESSAGE_TYPE m_message_type; 

	// Process id of the process sending the message.
	PROCESS_ID m_source_pid; 

	// Process id of the process receiving the message.
	PROCESS_ID m_destination_pid; 

public:
	
	~MsgEnv();
	MsgEnv();

	// Sets the type of the message.
	void set_type( MESSAGE_TYPE );

	// Returns the type of the message.
	MESSAGE_TYPE get_type();

	// Returns the sender of the message.
	PROCESS_ID get_source_pid();

	// The contents of the message.
	char m_data[ENVELOPE_SIZE];

	// Allow the kernel access to the message envelope.
	friend class Kernel; 
};

#endif
