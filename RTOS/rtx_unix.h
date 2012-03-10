/**
Header file with constants related to unix-rtx interaction.
**/

#ifndef RTX_UNIX_H
#define RTX_UNIX_H
#pragma once
#endif

#ifndef _WIN32
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#endif

#include <string.h>
#include <stdlib.h>

// File names for the shared memory files.
#define CRT_FILENAME "crt_sm_file"
#define KEYBOARD_FILENAME "kbd_sm_file"

// Size of the shared memory buffer.
#define BUFFER_SIZE 128

// The shared memory buffer will be treated by the rtx (and helper processes) as a character array.
typedef char buffer[BUFFER_SIZE];

// Define the signals which will get handled.
#define RSIGTIMER SIGALRM
#define RSIGKBD SIGUSR1
#define RSIGCRTW SIGVTALRM
#define RSIGCRTR SIGUSR2
#define RSIGTRM SIGINT
