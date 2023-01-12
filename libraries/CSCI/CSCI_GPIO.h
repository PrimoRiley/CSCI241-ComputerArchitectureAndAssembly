#ifndef INCLUDE_CSCI_GPIO_H
#define INCLUDE_CSCI_GPIO_H

#include <Arduino.h>

// GPIO port definitions

// Function prototypes

// Routine to return state (HIGH/LOW) of GPIO input pin.

int GetGPIOInputState(int pin);

// Routine to return level of GPIO analog input pin.
// Returns 0 = min voltage, 1023 = max voltage.

int GetGPIOAnalogInputLevel(int pin);

// Routine to return fractional level of GPIO analog input pin.
// Returns 0.0 = min voltage, 1.0 = max voltage.

double GetGPIOAnalogInputFraction(int pin);

// Routine to set GPIO output port bit states.
// Set all GPIO pins corresponding to 1 bits in the pattern byte
// to the "state" (HIGH/LOW) indicated.
//
// IMPORTANT: Port addresses are processor specific!

void SetGPIOutputPortState(uint8_t *portDataPtr, uint8_t bitPattern, int state);

// Routine to set GPIO output pin state (HIGH/LOW).

void SetGPIOOutputState(int pin, int state);

// Routine to set GPIO analog (PWM) output level (0 = min, 255 = max)

void SetGPIOAnalogOutput(int pin, int level);

// Routine to set GPIO analog (PWM) output level (0.0 = min, 1.0 = max)

void SetGPIOAnalogFraction(int pin, double fraction); 

// Routine to initialize an 8-bit GPIO port for input.
// Pass in the address of the port direction register.
//
// IMPORTANT: Port addresses are processor specific!

void SetupGPIOInputPort(uint8_t *portDirPtr);

// Routine to initialize a GPIO pin for input.

void SetupGPIOInputPin(int pin);

// Routine to initialize an 8-bit GPIO port for output.
// Pass in the address of the port direction register.
//
// IMPORTANT: Port addresses are processor specific!

void SetupGPIOOutputPort(uint8_t *portDirPtr);

// Routine to initialize a GPIO pin for output.

void SetupGPIOOutputPin(int pin);

#endif    // INCLUDE_CSCI_GPIO_H
