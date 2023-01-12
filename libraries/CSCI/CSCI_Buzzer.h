#ifndef INCLUDE_CSCI_BUZZER_H
#define INCLUDE_CSCI_BUZZER_H

// Definitions related to buzzers.

// Routine to set active buzzer on.  Sound will be emitted when on.

void SetActiveBuzzerOn(int pin);

// Routine to set active buzzer off.  Silent when off.

void SetActiveBuzzerOff(int pin);

// Routine to initialize an active buzzer connected to a GPIO pin

void SetupActiveBuzzer(int pin);

#endif    // INCLUDE_CSCI_BUZZER_H
