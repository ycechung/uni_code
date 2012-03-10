#include "process_welcome.h"

#include "rtx.h"

#include <string.h>

Process::ProcessTuple ProcessWelcome::process()
{
	return ProcessTuple( PROCESS_WELCOME, HIGH, 0 );
}

void ProcessWelcome::main()
{
	MsgEnv * pMsgEnv = RTX::request_msg_env();
	int pos = sprintf( pMsgEnv->m_data, "Welcome to RTOS v1.0 by Doug Sherk, James Anselm and Eugene Chung.\n" );
	pos += sprintf( &pMsgEnv->m_data[pos], "The OS is now ready for input. Please type \"h\" if you require assistance.\n" );
	RTX::send_console_chars( pMsgEnv );

	// Permanently block it.
	while ( true )
	{
		pMsgEnv = RTX::receive_message();
		RTX::release_msg_env( pMsgEnv );
	}
}

void ProcessWelcome::terminate()
{

}
