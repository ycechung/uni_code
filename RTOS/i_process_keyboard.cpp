/**
This file implements the keyboard i-process.
**/

#include "i_process_keyboard.h"
#include "rtx.h"
#include <signal.h>
#include <string.h>

// Return the process tuple.
Process::ProcessTuple IProcessKeyboard::process()
{
	return ProcessTuple( I_PROCESS_KEYBOARD, INVALID_PROCESS_PRIORITY, ( 1 << RSIGKBD ) );
}

IProcessKeyboard::IProcessKeyboard()
{

}

void IProcessKeyboard::main()
{
	// Check whether there is any data in the shared memory (ie. input from the keyboard).
	if ( * Kernel::m_keyboard_buffer != '\0' )
	{
		// Get an envelope sent by a process who wants keyboard input.
		MsgEnv * pMsgEnv = Kernel::receive_message();
		
		// Check whether an envelope was received (since i-processes don't block if there are no messages in its inbox.
		if ( pMsgEnv != NULL )
		{
			// Write input of the keyboard to the message envelope.
			strcpy( pMsgEnv->m_data, * Kernel::m_keyboard_buffer );

			// Set the first char in the shared memory to NULL so that the keyboard knows that it can write into it.
			(* Kernel::m_keyboard_buffer)[0] = '\0';	

			// Format the  message and send it back to the process who asked for keyboard input.
			PROCESS_ID dest_id = pMsgEnv->get_source_pid();
			pMsgEnv->set_type( CONSOLE_INPUT );
			Kernel::send_message( dest_id, pMsgEnv );
		}
	}
}

void IProcessKeyboard::terminate()
{

}
