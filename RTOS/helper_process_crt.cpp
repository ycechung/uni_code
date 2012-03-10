#ifndef _WIN32
#include <sys/shm.h>
#include <signal.h>
#include <sys/mman.h>
#endif

#include <assert.h>
#include "rtx_unix.h"
#include <cstring>
#include <cstdio>

// Pointer to the crt shared memory.
buffer * sm_ptr;

// Process id of the rtx.
int rtx_pid;

// Called when helper process receives a signal to terminate.
void terminate_process ( int /* signal */ )
{
	exit(0);
}

// Output data in the shared memory to the crt (ie. print it). Then clear the shared memory and notify the rtx that the data was output.
void output_chars( int /* signal */ )
{
#ifndef _WIN32
	// Check whether the buffer is empty. If it is, then don't do anything. It is has contents, then display them.
	if ( ( * sm_ptr )[0] != '\0' )
	{
		// Get the output and display it on the crt using printf.
		char output[BUFFER_SIZE];
		strcpy( output, ( * sm_ptr ) );
		printf( "%s", output );

		// Set the first char in the shared memory to null so that rtx knows that it can be written to.
		( * sm_ptr )[0] = '\0';	

		// Send a message to the rtx indicating that the characters were displayed.
		kill( rtx_pid, RSIGCRTW );
	}
#endif
}

int main( int /* argc */, char * argv[] )
{
#ifndef _WIN32
	// Get the buffer file id and rtx pid as parameters.
	int buffer_file_id = 0 ;
	sscanf( argv[1], "%d", &buffer_file_id );
	sscanf( argv[2], "%d", &rtx_pid );

	// Check that a valid file id was passed.
	if ( buffer_file_id < 1 )
	{
		printf( "crt - An invalid file id was passed. Terminating\n" );
		terminate_process( 0 );
	}

	// Initialize the shared memory pointer to the same memory segment as the rtx did.
	sm_ptr = ( buffer * ) mmap( 0, sizeof( buffer ), PROT_READ | PROT_WRITE, MAP_SHARED, buffer_file_id, 0 );
	
	// Check whether the shared memory pointer was initialized correctly.
	if ( sm_ptr == NULL )
	{
		printf( "Unable to create shared memory for the crt for crt helper process\n" );
		terminate_process(0);
	}

	// Set the helper process to terminate when SIGINT is received.
	sigset( SIGINT, &terminate_process );
	
	// Set the helper process to output characters when RSIGCRTR is received.
	sigset( RSIGCRTR, &output_chars );

	// Enter infinite loop waiting for signal from rtx to output chars or terminate.
	while ( true ) {}
#endif
}
