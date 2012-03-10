/**
This file implements process a.
**/

#include "process_a.h"
#include "rtx.h"
#include <string.h>


// Return the process tuple.
Process::ProcessTuple ProcessA::process()
{
	return ProcessTuple( PROCESS_A, HIGH, 0 );
}

void ProcessA::main()
{
	// Initialize the counter
	int m_counter = 0;
	
	// Receive message and deallocate it.
	MsgEnv * message = RTX::receive_message();
	RTX::release_msg_env(message);

	while( true )
	{
		// Get a message envelope.
		MsgEnv * count_message = RTX::request_msg_env();
		
		// Set contents of envelope and send it to process b.
		MESSAGE_TYPE count = COUNT_REPORT;
		count_message->set_type( count );
		sprintf( count_message->m_data, "%i", m_counter );
		RTX::send_message( PROCESS_B, count_message );

		// Increment the counter.
		m_counter++;

		// Release the processor.
		RTX::release_processor();
	}
}

void ProcessA::terminate()
{

}
