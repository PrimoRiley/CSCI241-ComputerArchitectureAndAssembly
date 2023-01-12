// Implementation of LED matrix routines

#include <Arduino.h>
#include <CSCI_Buzzer.h>
#include <CSCI_GPIO.h>

// ---------------------------------------------------------
void SetActiveBuzzerOn(int pin)
{
  SetGPIOOutputState(pin, HIGH);
}

// ---------------------------------------------------------
void SetActiveBuzzerOff(int pin)
{
  SetGPIOOutputState(pin, LOW);
}

// ---------------------------------------------------------
void SetupActiveBuzzer(int pin)
{
  SetupGPIOOutputPin(pin);
  SetActiveBuzzerOff(pin);
}
