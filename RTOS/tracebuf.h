/**
Header file for the trace buffers.
**/

#ifndef TRACEBUF_H
#define TRACEBUF_H
#ifdef _WIN32
#pragma once
#endif

#include <stdlib.h>
#include "rtx_base.h"

struct TraceBuffer
{
	PROCESS_ID destination_id;
	PROCESS_ID source_id;
	int time_stamp; // Time that the message transaction took place (in 100ms).
	MESSAGE_TYPE message_type;

	TraceBuffer();
	TraceBuffer( PROCESS_ID, PROCESS_ID, int, MESSAGE_TYPE );
};

#endif
