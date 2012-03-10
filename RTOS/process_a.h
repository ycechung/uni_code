/**
Header file for process a.
**/

#ifndef PROCESS_A_H
#define PROCESS_A_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx.h"

class ProcessA : private Process
{
	PROCESS_DECLARE()
};

#endif
