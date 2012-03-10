#ifndef MEMORY_H
#define MEMORY_H
#ifdef _WIN32
#pragma once
#endif

#include <assert.h>
#include <stdlib.h>

extern bool gInitialized;

// ensure that the "new" operator is only being used during rtx initialization.
#define WATCH_INITIALIZATION( type ) public: \
void * operator new( size_t size ) \
{ \
	assert( !gInitialized ); \
	return malloc( size ); \
}

#endif
