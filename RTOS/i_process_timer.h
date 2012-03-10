/**
Header file for the timer i-process.
**/

#ifndef I_PROCESS_TIMER_H
#define I_PROCESS_TIMER_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx.h"

class IProcessTimer : private Process
{
	PROCESS_DECLARE()
	
	// Queue containing message envelopes sent by processes waiting for a specified amount of time. The message is enqueued when the timer i-process receives it. It stays in the queue for the amount of time the message envelope specifies. Once that time has passed, the message is sent back to the process who sent the message to the crt i-process as a "wakeup". The queue is sorted using the sort_time_envelopes algorithm.
	rtx_stl::pqueue<MsgEnv> m_waiting_time;
	
	// An algorithm for sorting envelopes in the m_waiting_time queue. 
	static bool sort_timing_envelopes( MsgEnv * a, MsgEnv * b );

	// Gets the expiration time of the message envelope. 
	static int get_envelope_time( MsgEnv * a );

public:
	IProcessTimer();
};

#endif
