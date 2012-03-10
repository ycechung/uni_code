/**
This file implements process c.
**/

#include "process_c.h"
#include "rtx.h"
#include <string.h>

Process::ProcessTuple ProcessC::process()
{
	return ProcessTuple( PROCESS_C, LOW, 0 );
}

// Add a message to the local message queue.
int ProcessC::enqueue_local_message( MsgEnv * pMessage )
{
	// Get a node, assign the message envelope to it, and enqueue it to the local message queue.
	rtx_stl::node<MsgEnv> * pMessageNode = RTX::request_message_node();
	pMessageNode->set(pMessage);
	m_local_messages.enqueue(pMessageNode);
	return 1;
}

// Get a message from the local message queue.
MsgEnv * ProcessC::dequeue_local_message()
{
	// Get the message node from the local message queue.
	rtx_stl::node<MsgEnv> * pMessageNode = m_local_messages.dequeue();

	// Get the message from the node and release that node.
	MsgEnv * pMessage = pMessageNode->get();
	RTX::release_message_node( pMessageNode );
	return pMessage;
}

void ProcessC::main()
{
	while ( true )
	{
		
		// If the local message queue has messages in it, then read those messages first. Otherwise read messages from the inbox.
		MsgEnv * pMessage = m_local_messages.empty() ? RTX::receive_message() : dequeue_local_message();

		if( pMessage->get_type() == COUNT_REPORT )
		{
			// Get the count in the message.
			int count;
			sscanf( pMessage->m_data, "%i", &count );

			if( count % 20 == 0 )
			{
				// Output "Process C" to the screen.
				strcpy( pMessage->m_data, "Process C\n" );
				RTX::send_console_chars( pMessage );
				
				// Wait for acknowledgement from crt.
				while ( true )
				{
					// Look for acknowledgement message from the crt helper process. If other messages are received, add them to the local message queue to be dealt with later.
					pMessage = RTX::receive_message();
					if ( pMessage->get_type() == DISPLAY_ACK )
						break;			
					else
						enqueue_local_message( pMessage );
				}

				// Request 10 second delay.
				RTX::request_delay( 100, WAKEUP_CODE, pMessage );
				
				// Look for wakeup message from the timer i-process. If other messages are received, add them to the local message queue to be dealt with later.
				while ( true )
				{
					pMessage = RTX::receive_message();
					if ( pMessage->get_type() == WAKEUP_CODE )
						break;
					else
						enqueue_local_message(pMessage );
				}
			}
		}
		
		// Deallocate message and release processor.
		RTX::release_msg_env( pMessage );
		RTX::release_processor();
	}
}

void ProcessC::terminate()
{

}
