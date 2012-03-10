/**
This file implements the terminate i-process. This i-process is called when the user wants to terminate the rtx session.
**/

#include "i_process_terminate.h"
#include "rtx.h"
#include <signal.h>
#include <string.h>

// Return the process tuple.
Process::ProcessTuple IProcessTerminate::process()
{
	// TODO: Set this back.
	return ProcessTuple( I_PROCESS_TERMINATE, INVALID_PROCESS_PRIORITY, ( 1 << RSIGTRM ) );
}


IProcessTerminate::IProcessTerminate()
{
}

void IProcessTerminate::main()
{
	// Call the terminate function in the kernel.
	Kernel::terminate();
}

void IProcessTerminate::terminate()
{

}
