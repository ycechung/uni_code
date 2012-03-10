#include "rtx.h"
#include <string>

using namespace rtx_stl;

int RTX::register_process( Process * pProcess )
{
	ATOMIC( int, register_process( pProcess ) );
}

int RTX::send_message( PROCESS_ID dest_process_id, MsgEnv * msg_envelope )
{
	ATOMIC( int, send_message( dest_process_id, msg_envelope ) );
}

MsgEnv * RTX::receive_message()
{
	ATOMIC( MsgEnv *, receive_message() );
}

MsgEnv * RTX::request_msg_env()
{
	ATOMIC( MsgEnv * , request_msg_env() );
}

int RTX::release_msg_env( MsgEnv * msg_env_ptr )
{
	ATOMIC( int, release_msg_env( msg_env_ptr ) );
}

int RTX::release_processor()
{
	ATOMIC( int, release_processor() );
}

int RTX::request_process_status( MsgEnv * msg_env_ptr )
{
	ATOMIC( int, request_process_status( msg_env_ptr ) );
}

int RTX::terminate()
{
	ATOMIC( int, terminate() );
}

int RTX::change_priority( PROCESS_PRIORITY new_priority, PROCESS_ID target_process_id )
{
	ATOMIC( int, change_priority( new_priority, target_process_id ) );
}

int RTX::request_delay( int time_delay, MESSAGE_TYPE wakeup_code, MsgEnv * message_envelope )
{
	ATOMIC( int, request_delay( time_delay, wakeup_code, message_envelope ) );
}

int RTX::send_console_chars( MsgEnv * message_envelope )
{
	ATOMIC( int, send_console_chars( message_envelope ) );
}

int RTX::get_console_chars( MsgEnv * message_envelope )
{
	ATOMIC( int, get_console_chars( message_envelope ) );
}

int RTX::get_trace_buffers( MsgEnv * message_envelope)
{
	ATOMIC( int, get_trace_buffers( message_envelope ) );
}

rtx_stl::node<MsgEnv> * RTX::request_message_node()
{
	ATOMIC( rtx_stl::node<MsgEnv> *, request_message_node() );
}

int RTX::release_message_node( rtx_stl::node<MsgEnv> * pNode )
{
	ATOMIC( int, release_message_node( pNode ) );
}
