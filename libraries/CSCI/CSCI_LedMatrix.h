#ifndef INCLUDE_CSCI_LED_MATRIX_H
#define INCLUDE_CSCI_LED_MATRIX_H

#include <Arduino.h>
#include <LedControl.h>   // 8 x 8 LED matrix control library

// Definitions related to 8 x 8 LED matrix.

// The 8 x 8 LED matrix module is controlled using a MAX7219 IC.
// The Arduino communicates with the MAX7219 via a 3-wire
// serial interface.  Since turning on all 64 LEDs can draw
// 100+ ma, the module Vcc and GND is powered separately from a
// generic breadboard +5 volt power supply.  The 3-wire interface
// is controlled via three Arduino GPIO pins.

const int CSPin = 10;     // Chip Select GPIO pin
const int CLKPin = 11;    // Clock GPIO pin
const int DINPin = 12;    // Serial Data Input GPIO pin

const int MatAddr = 0;    // Address number (0) of our LED matrix.

// Define max number of rows and columns in the LED matrix.

const int NumMatRows = 8; // (0,1,...,NumMatRows-1)
const int NumMatCols = 8; // (0,1,...,NumMatCols-1)

// Function prototypes

// Routine to set an entire row of LEDs.
// The passed "row" value is the row (0,1,...,NumMatRows-1) to set.
// The passed "pattern" value contains one bit per LED,
// The MSB = leftmost LED, LSB = rightmost LED.
// Bit = 0, turn LED off.
// Bit = 1, turn LED on.

void SetLedRow(int row, uint8_t pattern);

// Routine to set a single LED on.

void SetLedOn(int row, int col);

// Routine to set a single LED off.

void SetLedOff(int row, int col);

// Clear entire LED matrix.  (Turn all LEDs off.)

void ClearLedMatrix();

// Routine to initialize the LED matrix module.

void SetupLedMatrix();

#endif    // INCLUDE_CSCI_LED_MATRIX_H
