/**
Header file for the terminate i-process.
**/

#ifndef I_PROCESS_TERMINATE_H
#define I_PROCESS_TERMINATE_H
#ifdef _WIN32
#pragma once
#endif

#include "rtx.h"

class IProcessTerminate : private Process
{
	PROCESS_DECLARE()

public:
	IProcessTerminate();
};

#endif
