/**
This file implements the process.
**/

#include "process.h"

Process::~Process()
{

}

// Return the process tuple.
Process::ProcessTuple::ProcessTuple( PROCESS_ID _id, PROCESS_PRIORITY _priority, int _signals_handled ) :
	id( _id ),
	priority( _priority ),
	signals_handled( _signals_handled )
{

}

// Return the status tuple.
Process::StatusTuple::StatusTuple( PROCESS_ID _id, PROCESS_PRIORITY _priority, PROCESS_STATUS _status ) :
	id( _id ),
	priority( _priority ),
	status( _status )
{

}
