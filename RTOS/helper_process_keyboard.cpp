#ifndef _WIN32
#include <sys/shm.h>
#include <sys/mman.h>
#include <signal.h>
#endif

#include <stdlib.h>
#include <assert.h>
#include "rtx_unix.h"
#include <cstring>
#include <cstdio>

// Pointer to the keyboard shared memeory.
buffer * sm_ptr;

// Process id of the rtx.
int rtx_pid;

// Called when the helper process receives a signal to terminate.
void terminate_process ( int /* signal */  )
{
	exit( 0 );
}

int main( int /* argc */, char * argv[] )
{
#ifndef _WIN32
 
	// Get the buffer file id and rtx pid as parameters.
	int buffer_file_id = 0;
	sscanf( argv[1], "%d", &buffer_file_id );
	sscanf( argv[2], "%d", &rtx_pid );
		
	// Check that a valid file id was passed.
	if ( buffer_file_id < 1 )
	{
		printf( "kbd - An invalid file id was passed. Terminating" );
		terminate_process( 0 );
	}
	
	// Initialize the shared memory pointer to the same memory segment as the rtx did.
	sm_ptr = ( buffer * ) mmap( NULL, sizeof( buffer ), PROT_READ | PROT_WRITE, MAP_SHARED, buffer_file_id, ( off_t ) 0 );

	// Check whether the shared memory pointer was initialized correctly.
	if ( sm_ptr == NULL )
	{
		printf( "kbd - Unable to create shared memory for the keyboard for keyboard helper process" );
		terminate_process( 0 );
	}

	// set the helper process to terminate when SIGINT is received.
	sigset( SIGINT, &terminate_process );

	// Enter an infinite loop to receive keyboad input.
	char c;
	int buffer_index = 0;
	while ( true )
	{
		// Get the first character from the keyboard since the last time the "return" key was pressed.
		c = getchar();

		// Check if the return key was pressed.
		if ( c != '\n' )
		{
			// If there is room in the buffer (leaving one extra space for the terminating character), then add it to the shared memory buffer.
			if ( buffer_index < BUFFER_SIZE - 1 )
				( * sm_ptr )[buffer_index++] = c;
		}
		else 
		{
			// Send RSIGKBD signal to rtx telling it to read buffer.
			( * sm_ptr )[buffer_index] = '\0';
			kill( rtx_pid, RSIGKBD );
			buffer_index = 0;	
		}
	}
#endif
}
