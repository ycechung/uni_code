/**
Header file for the process control block (pcb).
**/

#ifndef PCB_H
#define PCB_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx_base.h"
#include "process.h"
#include "msgenv.h"
#include <setjmp.h>

// Class definition for a generic PCB. Suitable for any process.
class PCB
{
	WATCH_INITIALIZATION( PCB );

protected:

	PROCESS_ID m_id;

	// Pointer to the process the pcb represents. 
	Process * m_model;
	rtx_stl::queue<MsgEnv> m_envelope_inbox;
	
	PCB( Process * );

public:
	~PCB();

	friend class Kernel;
};

// User PCB (for user processes) class definition.
class UPCB : public PCB
{
	WATCH_INITIALIZATION( UPCB );

protected:
	PROCESS_PRIORITY m_priority;
	PROCESS_STATUS m_status;
	byte * m_stack;
	jmp_buf m_context;

	UPCB( Process * );

public:
	~UPCB();

	friend class Kernel;
};

class IPCB : public PCB
{
	WATCH_INITIALIZATION( IPCB );

protected:
	
	// unix signals which the i-process handles.
	int m_signals_handled;

	IPCB( Process * );

public:
	~IPCB();

	friend class Kernel;
};

#endif
