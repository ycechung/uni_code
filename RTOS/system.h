#ifndef SYSTEM_H
#define SYSTEM_H
#ifdef _WIN32
#pragma once
#endif

typedef char byte;

#define ATOMIC( x, y ) \
	x returnVal; \
	Kernel::atomic( true ); \
	returnVal = Kernel::y; \
	Kernel::atomic( false ); \
	return returnVal;

#define ATOMIC2( x ) \
	Kernel::atomic( true ); \
	Kernel::x; \
	Kernel::atomic( false );

#ifdef _WIN32
#define SIGUSR1 30
#define SIGUSR2 31
#define SIGVTALRM 26
#define SIGALRM 14
#define SIGINT 2
#endif

#ifdef _WIN32
#pragma warning ( disable: 4996 )
#endif

#endif
