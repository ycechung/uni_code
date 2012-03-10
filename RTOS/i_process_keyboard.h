/**
Header file for the keyboard i-process.
**/

#ifndef I_PROCESS_KEYBOARD_H
#define I_PROCESS_KEYBOARD__H
#ifdef _WIN32
#pragma once
#endif

#include "rtx.h"

class IProcessKeyboard : private Process
{
	PROCESS_DECLARE()

public:
	IProcessKeyboard();
};

#endif

