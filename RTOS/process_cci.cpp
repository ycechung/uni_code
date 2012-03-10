#include "process_cci.h"

#include "rtx.h"

#include <string.h>

#define COMMAND_HANDLER( x ) else if ( strcmp( pMsgEnv->m_data, #x ) == 0 )
#define COMMAND_HANDLER_PARAM( x ) else if ( strncmp( pMsgEnv->m_data, #x, strlen( #x ) ) == 0 )

Process::ProcessTuple ProcessCCI::process()
{
	return ProcessTuple( PROCESS_CCI, HIGH, 0 );
}

void ProcessCCI::main()
{
	// A temporary location to store buffer information.
	static char buffer[ENVELOPE_SIZE];

	static MsgEnv * pMsgEnv;
	pMsgEnv = RTX::request_msg_env();

	while ( true )
	{
		strcpy( pMsgEnv->m_data, "CCI: \n" );
		RTX::send_console_chars( pMsgEnv );

		do
		{
			pMsgEnv = RTX::receive_message();
		} while ( pMsgEnv->get_type() != DISPLAY_ACK && RTX::release_msg_env( pMsgEnv ) );

		RTX::get_console_chars( pMsgEnv );
		do
		{
			pMsgEnv = RTX::receive_message();
		} while ( pMsgEnv->get_type() != CONSOLE_INPUT && RTX::release_msg_env( pMsgEnv ) );
		
		if ( false ) { }
		COMMAND_HANDLER( s )
		{
			RTX::send_message( PROCESS_A, pMsgEnv );

			pMsgEnv = RTX::request_msg_env();
		}
		COMMAND_HANDLER( ps )
		{
			RTX::request_process_status( pMsgEnv );

			int num = ( int ) pMsgEnv->m_data[0], pos = 0;
			byte * data = &pMsgEnv->m_data[1];

			pos += sprintf( &buffer[pos], "PROCESS STATUS\n" );
			pos += sprintf( &buffer[pos], "PID    PRI    STAT\n" );
			for ( int i = 0; i < num && pos < ENVELOPE_SIZE; i++ )
			{
				Process::StatusTuple * pStatusTuple = reinterpret_cast<Process::StatusTuple *>( &data[i * sizeof( StatusTuple )] );
				pos += sprintf( &buffer[pos], "%-6d %-6d %-6d\n", pStatusTuple->id, pStatusTuple->priority, pStatusTuple->status );
			}
			pos += sprintf( &buffer[pos], "Total processes: %d\n", num );

			strcpy( pMsgEnv->m_data, buffer );

			RTX::send_console_chars( pMsgEnv );

			do
			{
				pMsgEnv = RTX::receive_message();
			} while ( pMsgEnv->get_type() != DISPLAY_ACK && RTX::release_msg_env( pMsgEnv ) );
		}
		COMMAND_HANDLER ( cl )
		{
			// Write newline characters into a message envelope.
			int i = 0;
			for ( ; i < 60; i++ )
				pMsgEnv->m_data[i] = '\n';
		
			// Add null terminating character
			pMsgEnv->m_data[i + 1] = '\0';
	
			// Send the message to the console to print the newlines to "clear" the screen.
			RTX::send_console_chars( pMsgEnv );
			
			// Wait for confirmation that the message was output to the screen.
			do
			{
				pMsgEnv = RTX::receive_message();
			} while ( pMsgEnv->get_type() != DISPLAY_ACK && RTX::release_msg_env( pMsgEnv ) );

		}
		COMMAND_HANDLER( cd )
		{
			pMsgEnv->m_data[0] = 1;
			pMsgEnv->set_type( CLOCK_TOGGLE );
			RTX::send_message( PROCESS_WALLCLOCK, pMsgEnv );
			pMsgEnv = RTX::request_msg_env();
		}
		COMMAND_HANDLER( ct )
		{
			pMsgEnv->m_data[0] = 0;
			pMsgEnv->set_type( CLOCK_TOGGLE );
			RTX::send_message( PROCESS_WALLCLOCK, pMsgEnv );
			pMsgEnv = RTX::request_msg_env();
		}
		COMMAND_HANDLER_PARAM( c )
		{
			int hours, minutes, seconds;
			sscanf( &pMsgEnv->m_data[2], "%d:%d:%d", &hours, &minutes, &seconds );

			if ( hours > 23 || minutes > 59 || seconds > 59 || strlen( pMsgEnv->m_data ) < strlen( "c xx:yy:zz" ) )
			{
				strcpy( pMsgEnv->m_data, "Invalid time provided\n" );

				pMsgEnv->set_type( ERROR_REASON );
				RTX::send_console_chars( pMsgEnv );

				do
				{
					pMsgEnv = RTX::receive_message();
				} while ( pMsgEnv->get_type() != DISPLAY_ACK && RTX::release_msg_env( pMsgEnv ) );
			}
			else
			{
				pMsgEnv->m_data[0] = hours;
				pMsgEnv->m_data[1] = minutes;
				pMsgEnv->m_data[2] = seconds;
				pMsgEnv->m_data[3] = '\0';
				pMsgEnv->set_type( CLOCK_SET );
				RTX::send_message( PROCESS_WALLCLOCK, pMsgEnv );
				pMsgEnv = RTX::request_msg_env();
			}
		}
		COMMAND_HANDLER( b )
		{
			RTX::get_trace_buffers( pMsgEnv );

			int num = ( int ) pMsgEnv->m_data[0], pos = 0;
			byte * data = &pMsgEnv->m_data[2];

			pos += sprintf( &buffer[pos], "-- SEND BUFFERS --\n" );
			pos += sprintf( &buffer[pos], "DEST   SRC    TIME\n" );
			for ( int i = 0; i < num && pos < ENVELOPE_SIZE; i++ )
			{
				TraceBuffer * pTraceBuffer = reinterpret_cast<TraceBuffer *>( &data[i * sizeof( TraceBuffer )] );
				pos += sprintf( &buffer[pos], "%-6d %-6d %-6d %-6d\n", pTraceBuffer->destination_id, pTraceBuffer->source_id, pTraceBuffer->time_stamp, pTraceBuffer->message_type );
			}

			data = &pMsgEnv->m_data[2 + num * sizeof( TraceBuffer )];
			num = ( int ) pMsgEnv->m_data[1];
			pos += sprintf( &buffer[pos], "-- RECEIVE BUFFERS --\n" );
			pos += sprintf( &buffer[pos], "DEST   SRC    TIME   TYPE\n" );
			for ( int i = 0; i < num && pos < ENVELOPE_SIZE; i++ )
			{
				TraceBuffer * pTraceBuffer = reinterpret_cast<TraceBuffer *>( &data[i * sizeof( TraceBuffer )] );
				pos += sprintf( &buffer[pos], "%-6d %-6d %-6d %-6d\n", pTraceBuffer->destination_id, pTraceBuffer->source_id, pTraceBuffer->time_stamp, pTraceBuffer->message_type );
			}
			pos += sprintf( &buffer[pos], "Total trace buffers: %d\n", ( int ) pMsgEnv->m_data[0] + ( int ) pMsgEnv->m_data[1] );

			// Copy from our buffer to the message envelope.
			strcpy( pMsgEnv->m_data, buffer );

			RTX::send_console_chars( pMsgEnv );

			do
			{
				pMsgEnv = RTX::receive_message();
			} while ( pMsgEnv->get_type() != DISPLAY_ACK && RTX::release_msg_env( pMsgEnv ) );
		}
		COMMAND_HANDLER( t )
		{
			RTX::terminate();
			return;
		}
		COMMAND_HANDLER_PARAM( n )
		{
			PROCESS_ID process_id;
			PROCESS_PRIORITY priority;
			
			sscanf( &pMsgEnv->m_data[2], "%d %d", reinterpret_cast<int *>( &priority ), reinterpret_cast<int *>( &process_id ) );

			if ( strlen( pMsgEnv->m_data ) < strlen( "n x y" ) ||  !RTX::change_priority( priority, process_id ) )
			{
				strcpy( pMsgEnv->m_data, "Failed to set process priority\n" );

				pMsgEnv->set_type( ERROR_REASON );
				RTX::send_console_chars( pMsgEnv );

				do
				{
					pMsgEnv = RTX::receive_message();
				} while ( pMsgEnv->get_type() != DISPLAY_ACK && RTX::release_msg_env( pMsgEnv ) );
			}
		}
		COMMAND_HANDLER_PARAM( e )
		{
			strcpy( buffer, &pMsgEnv->m_data[strlen( "e" ) + 1] );
			sprintf( pMsgEnv->m_data, "%s\n", buffer );

			RTX::send_console_chars( pMsgEnv );
			
			do
			{
				pMsgEnv = RTX::receive_message();
			} while ( pMsgEnv->get_type() != DISPLAY_ACK && RTX::release_msg_env( pMsgEnv ) );
		}
		COMMAND_HANDLER( h )
		{
			int pos = 0;
			pos += sprintf( &pMsgEnv->m_data[pos], "Available commands:\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "s	- begin user demonstration\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "ps	- show status of all processes\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "cl	- clear the screen\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "cd	- enable wall clock\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "ct	- disable wall clock\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "c	- [parameters: (hh:mm:ss)] set wall clock time\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "b	- display trace buffers\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "t	- terminate OS\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "n	- [parameters: (priority) (pid)] set process priority\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "e	- [parameters: (message)] prints out input\n" );
			pos += sprintf( &pMsgEnv->m_data[pos], "h	- displays this menu\n" );

			RTX::send_console_chars( pMsgEnv );
			
			do
			{
				pMsgEnv = RTX::receive_message();
			} while ( pMsgEnv->get_type() != DISPLAY_ACK && RTX::release_msg_env( pMsgEnv ) );
		}
		else
		{
			strcpy( pMsgEnv->m_data, "Invalid command\n" );

			pMsgEnv->set_type( ERROR_REASON );
			RTX::send_console_chars( pMsgEnv );
			
			do
			{
				pMsgEnv = RTX::receive_message();
			} while ( pMsgEnv->get_type() != DISPLAY_ACK && RTX::release_msg_env( pMsgEnv ) );
		}
	}
}

void ProcessCCI::terminate()
{

}
