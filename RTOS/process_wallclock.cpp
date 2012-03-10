/**
This file implements the wall clock process.
**/

#include "process_wallclock.h"
#include "rtx.h"
#include <string.h>

ProcessWallclock::ProcessWallclock() : m_clock_toggled( false ),
									   m_current_time( 0 )
{

}

Process::ProcessTuple ProcessWallclock::process()
{
	return ProcessTuple( PROCESS_WALLCLOCK, LOW, 0 );
}

// Add a message to the local message queue.
int ProcessWallclock::enqueue_local_message( MsgEnv * pMessage )
{
	// Get a node, assign the message envelope to it, and enqueue it to the local message queue.
	rtx_stl::node<MsgEnv> * pMessageNode = RTX::request_message_node();
	pMessageNode->set(pMessage);
	m_local_messages.enqueue(pMessageNode);
	return 1;
}

// Get a message from the local message queue.
MsgEnv * ProcessWallclock::dequeue_local_message()
{
	// Get the message node from the local message queue.
	rtx_stl::node<MsgEnv> * pMessageNode = m_local_messages.dequeue();

	// Get the message from the node and release that node.
	MsgEnv * pMessage = pMessageNode->get();
	RTX::release_message_node( pMessageNode );
	return pMessage;
}

void ProcessWallclock::main()
{
	// Request a delay of 1 second.
	MsgEnv * pMsgEnv = RTX::request_msg_env();
	RTX::request_delay( 10, WAKEUP_CODE, pMsgEnv );

	while ( true )
	{
	    // Get an envelope sent by a process who wants to change or set wall clock.
		pMsgEnv = RTX::receive_message();
        
		// Perform an action based on the type of message received.
		switch ( pMsgEnv->get_type() )
		{
        
		// Set the clock toggle.
		case CLOCK_TOGGLE:
			m_clock_toggled = pMsgEnv->m_data[0] == 1 ? true : false;
			RTX::release_msg_env( pMsgEnv );
			break;
        
		// Set the clock.
		case CLOCK_SET:
			m_current_time = pMsgEnv->m_data[0]*3600 + pMsgEnv->m_data[1]*60 + pMsgEnv->m_data[2];
			RTX::release_msg_env( pMsgEnv );
			break;
		
		// Increment the current time and output the time to the screen if the clock is enabled.
		case WAKEUP_CODE:

            // One second after 23:59:59, time resets to 00:00:00.
			m_current_time %= 86400;
			
			// If the clock is toggled, display the current time on the screen.
			if ( m_clock_toggled )
			{
			    // Format the internel clock to display in xx:yy:zz format where xx = hours, yy = minutes, and zz = seconds.
				sprintf( pMsgEnv->m_data, "%02u:%02u:%02u\n", ( m_current_time / 3600 ) % 24, ( m_current_time / 60 ) % 60, m_current_time % 60 );
				
				// Display the time.
				RTX::send_console_chars( pMsgEnv );
				
				// Wait for acknowledgement from the crt that the time was displayed.
				while ( true )
				{
					// Look for acknowledgement message from the crt helper process. If other messages are received, add them to the local message queue to be dealt with later.
					pMsgEnv = RTX::receive_message();
					if ( pMsgEnv->get_type() == DISPLAY_ACK )
						break;			
					else
						enqueue_local_message( pMsgEnv );
				}
			}
           
			// Request a 1 second delay and increment the current time.
			RTX::request_delay( 10, WAKEUP_CODE, pMsgEnv );
			m_current_time++;
			break;
		
		// Discard the message.
		default:

			RTX::release_msg_env( pMsgEnv );
			break;
		}
	}
}

void ProcessWallclock::terminate()
{

}
