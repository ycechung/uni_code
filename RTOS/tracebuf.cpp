/** 
File implementing the trace buffer.
**/

#include "tracebuf.h"
#include "rtx_base.h"

TraceBuffer::TraceBuffer() :
	destination_id( INVALID_PROCESS_ID ),
	source_id( INVALID_PROCESS_ID ),
	time_stamp( 0 ),
	message_type( INVALID_MESSAGE_TYPE )
{

}

TraceBuffer::TraceBuffer( PROCESS_ID _destination_id, PROCESS_ID _source_id, int _time_stamp, MESSAGE_TYPE _message_type ) :
	destination_id( _destination_id ),
	source_id( _source_id ),
	time_stamp( _time_stamp ),
	message_type( _message_type )
{

}
