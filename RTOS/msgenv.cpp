/**
File implementing the message envelope.
**/

#include "msgenv.h"

MsgEnv::MsgEnv()
{

}

MsgEnv::~MsgEnv()
{

}

// Return the type of the message.
MESSAGE_TYPE MsgEnv::get_type()
{
	return m_message_type;
}

// Set the type of the message.
void MsgEnv::set_type( MESSAGE_TYPE msg_type )
{
	m_message_type = msg_type;
}

// Return the sender of the message.
PROCESS_ID MsgEnv::get_source_pid()
{
	return m_source_pid;
}
