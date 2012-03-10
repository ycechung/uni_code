/**
This file contains constants used by the rtx.
**/

#ifndef RTX_CONST_H
#define RTX_CONST_H
#ifdef _WIN32
#pragma once
#endif

// Number of trace entries for each trace buffer
#define TRACE_NUM 16

// Number of envelopes available for inter-process communication.
#define ENVELOPE_NUM 16

// The amount of data which a single message envelope can store (in bytes).
#define ENVELOPE_SIZE 1024

// The amount of data which a process' stack can store (in bytes).
#define PROCESS_STACK_SIZE 16384

// Each enum constains two special members:
// - invalid - represents an invalid member in the enum. It is always the first in the enum (ie. 0).
// - size - represents the number of members in the enum. It is placed at the end of the enum so that its value is always the number of members.

// The different types of priorities which a process can have. The processes higher in the list have a higher priority.
enum PROCESS_PRIORITY 
{
	INVALID_PROCESS_PRIORITY,
	HIGH,
	MEDIUM,
	LOW,
	IDLE, // Only null process would have this priority.
	PROCESS_PRIORITY_SIZE
};

// The different types of identifiers a process can have. Each identifier can be used by at most one process.
enum PROCESS_ID 
{
	INVALID_PROCESS_ID,
	PROCESS_NULL,
	PROCESS_A,
	PROCESS_B,
	PROCESS_C,
	PROCESS_CCI,
	PROCESS_WALLCLOCK,
	PROCESS_WELCOME,
	I_PROCESS_TIMER,
	I_PROCESS_KEYBOARD,
	I_PROCESS_CRT,
	I_PROCESS_TERMINATE,
	PROCESS_ID_SIZE
};

// The different states a process can be in.
enum PROCESS_STATUS
{
	INVALID_PROCESS_STATUS,
	EXECUTING, // The process is being executed.
	READY, // The process is ready for execution.
	BLOCK_ENV_CLAIM, // The process is waiting for an available envelope.
	BLOCK_ENV_RECEIVE, // The process is waiting for an envelope in its inbox.
	INTERRUPTED, // The process is being interrupted.
	PROCESS_STATUS_SIZE
};

// The different types of message envelopes
enum MESSAGE_TYPE
{
	INVALID_MESSAGE_TYPE,
	ALL_PROCESS, // Message contains the current status and priority of all the processes.
	DISPLAY_REQ, // Message contains characters to be output to the crt.
	DISPLAY_ACK, // Acknowledges transmission of message from UART.
	CONSOLE_INPUT, // Message contains the characters received from the console.
	TRACE_BUFFER, // Message contains the trace buffers for send and receive primitives.
	CLOCK_TOGGLE, // Message contains instruction on whether to display the clock.
	CLOCK_SET, // Message with value to set wall clock with.
	ERROR_REASON, // Message with an error to send to the crt.
	COUNT_REPORT, // Message is used for process a.
	WAKEUP_CODE, // Notifies process that timeout delay is complete.
	MESSAGE_TYPE_SIZE
};

#endif
