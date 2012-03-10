/**
Header file for the process.
**/

#ifndef PROCESS_H
#define PROCESS_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx_base.h"

// Registers the process.
#define PROCESS_REGISTER( x ) \
	x * p##x = new x; \
	RTX::register_process( ( Process * ) p##x );

// Common declarations to all processes.
#define PROCESS_DECLARE() \
public: \
	void main(); \
	void terminate(); \
	ProcessTuple process(); \
	\
	friend class Kernel;

class Process
{
public:
	
	// Contains information about the process.
	struct ProcessTuple
	{
		PROCESS_ID id;
		
		// For user processes only.
		PROCESS_PRIORITY priority;
		
		// For i-processes only.
		int signals_handled;

		// Return the process tuple.
		ProcessTuple( PROCESS_ID, PROCESS_PRIORITY, int );
	};

	// Contains information about the process, including its sataus.
	struct StatusTuple
	{
		PROCESS_ID id;
		PROCESS_PRIORITY priority;
		PROCESS_STATUS status;

		// Return the status tuple.
		StatusTuple( PROCESS_ID, PROCESS_PRIORITY, PROCESS_STATUS );
	};

	// Entry point of the process.
	virtual void main() = 0;
	// Sort of a dtor, but the process class itself is not actually destroyed; only the PCB.
	virtual void terminate() = 0;
	// Returns process information.
	virtual ProcessTuple process() = 0;

	virtual ~Process();
};

#endif
