/**
Header file for the crt i-process.
**/

#ifndef I_PROCESS_CRT_H
#define I_PROCESS_CRT_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx.h"

class IProcessCRT : private Process
{
	PROCESS_DECLARE()

private:

	// Stores a message envelope after its data are written to shared memory. Once the crt i-process is notified that the data was output to the screen, the message envelope is sent back to the process who sent the message.
	MsgEnv * m_waiting_for_print;

	// A buffer used to store the message which the crt is to display.
	// This variable is important when the size of the shared memory for the crt is smaller than the size of the message envelope.
	//When this is the case, the first chunk of data from the message envelope is copied to the shared memory
	//and the crt helper process is signaled to output the contents of the shared memory.
	//When the crt i process gets confirmation that the first chunk was output to the screen, the next chunk of data is written to the shared memory
	//and the crt helper process is signaled again. This process is repeated until the entire contents of the message envelope have been displayed.
	char m_local_buffer[ENVELOPE_SIZE];

	// A counter to determine how much of the message data of the message envelope currently being handled has already been output to the screen.
	unsigned int m_local_buffer_pos;

public:
	IProcessCRT();
};

#endif

