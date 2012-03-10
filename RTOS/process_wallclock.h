/**
Header file for the wallclock process
**/

#ifndef PROCESS_WALLCLOCK_H
#define PROCESS_WALLCLOCK_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx.h"

class ProcessWallclock : private Process
{
private:
	
	// Holds messages which were received from the inbox but not yet handled.
	rtx_stl::queue<MsgEnv> m_local_messages;

	// Add a message to the local message queue.
	int enqueue_local_message( MsgEnv * message );

	// Get a message from the local message queue.
	MsgEnv * dequeue_local_message();

	// Indication whether the clock should be displayed to the screen or not.
	bool m_clock_toggled;
	unsigned int m_current_time;

	PROCESS_DECLARE()

	ProcessWallclock();
};

#endif
