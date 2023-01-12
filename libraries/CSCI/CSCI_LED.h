#ifndef INCLUDE_CSCI_LED_H
#define INCLUDE_CSCI_LED_H

#include <CSCI_GPIO.h>
#include <Arduino.h>

// LED definitions

// Function prototypes

// Routine to set LEDs corresponding to bits of a 8-bit GPIO port.
// If the bit is 1, the LED is set to the "state" (HIGH/LOW).
//
// IMPORTANT: Port addresses are processor dependent!

void SetLEDPortBits(uint8_t *portDataPtr, uint8_t bits, int state);

// Routine to set LEDs corresponding to bits in a byte.
// The bits are designated (0,1,2,..,7) where 0 is the LSB and 7 the MSB.
// "bitToPin" is an array which maps the bit number to each GPIO pin.
// If the bit is 1, the LED is set to "state" (HIGH/LOW).

void SetLEDByteState(uint8_t byte, const int bitToPin[8], int state);

// Routine to set LED pin state (HIGH/LOW).

void SetLEDState(int pin, int state);

// Routine to initialize an 8-bit LED group connected to a GPIO port.
// Pass in the address of the port direction register.
//
// IMPORTANT: Port addresses are processor dependent!

void SetupLEDPort(uint8_t *portDirPtr);

// Routine to initialize LED GPIO pins corresponding to bits in a byte.
// The bits are designated (0,1,2,..,7) where 0 is the LSB and 7 the MSB.
// "bitToPin" is an array which maps the bit number to each GPIO pin.

void SetupLEDByte(const int bitToPin[8]);

// Routine to initialize an LED pin for output.

void SetupLED(int pin);

#endif    // INCLUDE_CSCI_LED_H
