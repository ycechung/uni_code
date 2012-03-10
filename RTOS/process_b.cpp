/**
This file implements process b.
**/

#include "process_b.h"
#include "rtx.h"
#include <string.h>

// Return the process tuple.
Process::ProcessTuple ProcessB::process()
{
	return ProcessTuple( PROCESS_B, LOW, 0 );
}

void ProcessB::main()
{
	while ( true )
	{
		// Receive a message (assumed to be from process a) and then send it to process c.
		MsgEnv * message = RTX::receive_message();
		RTX::send_message( PROCESS_C, message );
	}
}

void ProcessB::terminate()
{

}
