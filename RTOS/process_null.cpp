/**
This file implements the null process.
**/

#include "process_null.h"
#include "rtx.h"
#include <string.h>

Process::ProcessTuple ProcessNull::process()
{
	return ProcessTuple( PROCESS_NULL, IDLE, 0 );
}

void ProcessNull::main()
{
	// Continuously release the processor.
	while ( true )
	{
		RTX::release_processor();
	}
}

void ProcessNull::terminate()
{

}
