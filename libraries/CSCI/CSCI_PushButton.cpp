// Pushbutton utility routines.

#include <CSCI_PushButton.h>
#include <CSCI_GPIO.h>
#include <CSCI_Timers.h>
#include <Arduino.h>

// ---------------------------------------------------------
int WaitForEitherButtonClick(int buttonAPin, int buttonBPin)
{
  while ( true )
  {
    if ( IsButtonPressed(buttonAPin) )
    {
      WaitForButtonClick(buttonAPin);
      return buttonAPin;
    }
  
    if ( IsButtonPressed(buttonBPin) )
    {
      WaitForButtonClick(buttonBPin);
      return buttonBPin;
    }
  }    
}

// ---------------------------------------------------------
void WaitForButtonClick(int pin)
{
  WaitForButtonPress(pin);
  WaitForButtonRelease(pin);
};

// ---------------------------------------------------------
void WaitForButtonPress(int pin)
{
  // Wait until button stays pressed for a minimum amount of time.

  const int minPressTime = 50;    // Min press time (in milliseconds)
  
  do
  {
    // Wait for initial button contact.
  
    while ( !IsButtonPressed(pin) )
      { }
  
    // Now wait a small time for button debounce.
  
    WaitMillis(minPressTime);
    
  } while ( !IsButtonPressed(pin) );
}

// ---------------------------------------------------------
void WaitForButtonRelease(int pin)
{
  // Wait until button stays released for a minimum amount of time.

  const int minReleaseTime = 50;  // Min release time (in milliseconds)
  
  do
  {
    // Wait for initial button release.
  
    while ( IsButtonPressed(pin) )
      { }
  
    // Now wait a small time for button debounce.
  
    WaitMillis(minReleaseTime);
    
  } while ( IsButtonPressed(pin) );
}

// ---------------------------------------------------------
bool IsButtonPressed(int pin)
{
  return ( GetGPIOInputState(pin) == LOW ); // Active button LOW
}

// ---------------------------------------------------------
void SetupButton(int pin)
{
  SetupGPIOInputPin(pin);
}
