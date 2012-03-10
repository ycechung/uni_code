/**
Header file for the null process.
**/

#ifndef PROCESS_NULL_H
#define PROCESS_NULL_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx.h"

class ProcessNull : private Process
{
	PROCESS_DECLARE()
};

#endif
