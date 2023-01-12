#ifndef INCLUDE_CSCI_PUSH_BUTTON_H
#define INCLUDE_CSCI_PUSH_BUTTON_H

// Pushbutton utility definitions

// Function prototypes

// Routine to wait for either button to be clicked.
// Returns the pin number of the button that was clicked.

int WaitForEitherButtonClick(int buttonAPin, int buttonBPin);

// Routine to wait for the pusbutton to be "clicked",
// (i.e., pressed and then released).

void WaitForButtonClick(int pin);

// Routine to wait for the pushbutton connected to a GPIO
// pin to be pressed.

void WaitForButtonPress(int pin);

// Routine to wait for the pushbutton connected to a GPIO
// pin to be released.

void WaitForButtonRelease(int pin);

// Immediately returns "true" if button is pressed, false if not.

bool IsButtonPressed(int pin);

// Routine to initialize a GPIO pin that senses a pushbutton.

void SetupButton(int pin);

#endif    // INCLUDE_CSCI_PUSH_BUTTON_H
