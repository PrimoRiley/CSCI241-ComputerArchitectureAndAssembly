#ifndef INCLUDE_CSCI_CONSOLE_H
#define INCLUDE_CSCI_CONSOLE_H

#include <Arduino.h>  // Contains String object and other definitions

// Prototypes for console display and keyboard utilities

void ConsoleSetup();                      // Initialize the console;
void DisplayInteger(int value);           // Display default integer.
void DisplayInteger(uint8_t value);       // Display 8-bit unsigned integer.
void DisplayInteger(uint16_t value);      // Display 16-bit unsigned integer.
void DisplayInteger(int32_t value);       // Display 32-bit integer.
void DisplayInteger(uint32_t value);      // Display 32-bit unsigned integer.
void DisplayDouble(double value, size_t numDecimals); // Display floating point.
void DisplayAsBinary(char value);         // Display char as binary.
void DisplayAsBinary(uint8_t value);      // Display unsigned byte as binary.
void DisplayAsBinary(uint16_t value);     // Display unsigned integer as binary.
void DisplayError(const String& errMsg);  // Display error message, then pause.
void DisplayPause();                      // Display pause message, then wait.
void DisplayString(const String& str);    // Display string on the console.
void DisplayNewline();                    // Advance display to next line.

String KeyboardGetline();   // Get a line of input from the keyboard.

#endif    // INCLUDE_CSCI_CONSOLE_H
