#ifndef INCLUDE_SYS_UTILS_H
#define INCLUDE_SYS_UTILS_H

// Definitions for system-wide utility routines.

#include <Arduino.h>

// This is GCC compiler attribute to disable automatic initialization of
// a C/C++ global variable to zero.

#define CSCI_NOINIT __attribute__ ((section(".noinit")))

// Map HIGH/LOW state value to state string ("HIGH" or "LOW").

String GetStateName(int state);

// Call this routine when an internal program error occurs.
// Pass in the source code file name __FILE__, and line number __LINE__.

void InternalError(const char *sourceFile, int sourceLine);

// Halt the program

void HaltProgram();

#endif INCLUDE_SYS_UTILS_H
