/**
This file implements the crt i-process
**/

#include "i_process_crt.h"
#include "rtx.h"
#include <signal.h>
#include <string.h>

int min( int a, int b )
{
	return a < b ? a : b;
}

// Return the process tuple.
Process::ProcessTuple IProcessCRT::process()
{
	return ProcessTuple( I_PROCESS_CRT, INVALID_PROCESS_PRIORITY, ( 1 << RSIGCRTW ) | ( 1 << RSIGCRTR ) );
}

// Initialize the crt i-process. Set the "waiting" envelope pointer to NULL.
IProcessCRT::IProcessCRT() : 
	m_waiting_for_print( NULL )
{

}

void IProcessCRT::main()
{
	// The crt i-process handles two different signals. Its functionality is dependent on which signal was sent. 
	switch ( Kernel::m_current_signal_handled )
	{
		// Hack in the curly brackets here so we don't get initialization errors.
		// Notify the process who asked for data to be output that the data was successfully displayed.
		case RSIGCRTW:
		{
			// Check if the all the contents of the message envelope were displayed. If not, then add the next chunk of the message into the buffer and signal the crt helper process to output that chunk of data.
			if ( ++m_local_buffer_pos * BUFFER_SIZE < strlen( m_local_buffer ) )
			{
				strncpy( *Kernel::m_crt_buffer, &m_local_buffer[BUFFER_SIZE * m_local_buffer_pos], BUFFER_SIZE);
#ifndef _WIN32
				kill( Kernel::m_crt_helper_pid, SIGUSR2 );
#endif
				break;
			}
			else
			{
				// Format message for being sent back to process who asked for characters to be sent
				PROCESS_ID dest_id = m_waiting_for_print->get_source_pid();
				m_waiting_for_print->set_type( DISPLAY_ACK );

				// Send the message to the process
				Kernel::send_message( dest_id, m_waiting_for_print );
			
				// Since the message envelope was sent back to the process, set the "waiting" pointer to null so that the crt i-process knows that the shared memory can be safely overwritten.
				m_waiting_for_print = NULL;

				// Don't break, so that the contents get read in case anything was waiting.
			}
		}
			
		// Write data into the shared memory for the crt helper process to output to the screen.
		case RSIGCRTR: 
		{
			// Check if the data in the buffer is still waiting to be output. If it is, then don't overwrite it.
			if ( m_waiting_for_print != NULL )
				break;

			// Receive the message with data to write to the shared memory.
			MsgEnv * pMsgEnv = Kernel::receive_message();
			
			// Check whether any message was received (since i-process doesn't block if there's no message to receive).
			if ( pMsgEnv != NULL )
			{
				// write output to the crt buffer
				strcpy( m_local_buffer, pMsgEnv->m_data );
				strncpy( *Kernel::m_crt_buffer, m_local_buffer, BUFFER_SIZE );

				// Set the buffer position to 0.
				m_local_buffer_pos = 0;
				
				// Store the message envelope until the crt i-process gets confirmation that the data was output to the screen.
				m_waiting_for_print = pMsgEnv;

#ifndef _WIN32
				// Send a signal to the crt helper process to output the data in the shared memory.
				kill( Kernel::m_crt_helper_pid, SIGUSR2 );
#endif
			}

			break;
		}
	}
}

void IProcessCRT::terminate()
{
}
