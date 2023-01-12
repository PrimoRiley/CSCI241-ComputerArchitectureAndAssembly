// GPIO Output routines.

#include <CSCI_GPIO.h>

// ---------------------------------------------------------
int GetGPIOInputState(int pin)
{
  return digitalRead(pin);
}

// ---------------------------------------------------------
int GetGPIOAnalogInputLevel(int pin)
{
  return analogRead(pin);
}

// ---------------------------------------------------------
double GetGPIOAnalogInputFraction(int pin)
{
  int level = GetGPIOAnalogInputLevel(pin);
  
  return static_cast<double>(level) / 1023.0;
}

// ---------------------------------------------------------
void SetGPIOutputPortState(uint8_t *portDataPtr, uint8_t bitPattern, int state)
{
  // Fetch current state of all output pins.
    
  uint8_t portBits = *portDataPtr;

  if ( state == HIGH )
  {
    // Set the indicated pins to "1"
    
    portBits = portBits | bitPattern;
  }
  else
  {
    // Set the indicated pins to "0"
    
    portBits = portBits & ~bitPattern;
  }
  
  // Update state of port bits.
  
  *portDataPtr = portBits;
  

}

// ---------------------------------------------------------
void SetGPIOOutputState(int pin, int state)
{
  digitalWrite(pin, state);
}

// ---------------------------------------------------------
void SetGPIOAnalogOutput(int pin, int level)
{
  analogWrite(pin, level);
}

// ---------------------------------------------------------
void SetGPIOAnalogFraction(int pin, double fraction)
{
  int level = static_cast<int>(fraction * 255.0 + 0.5);
  SetGPIOAnalogOutput(pin, level);
}

// ---------------------------------------------------------
void SetupGPIOInputPort(uint8_t *portDirPtr)
{
  *portDirPtr = 0x00; // Set all direction bits to indicate INPUT.
}

// ---------------------------------------------------------
void SetupGPIOInputPin(int pin)
{
  pinMode(pin, INPUT);
}

// ---------------------------------------------------------
void SetupGPIOOutputPort(uint8_t *portDirPtr)
{
  *portDirPtr = 0xFF; // Set all direction bits to indicate OUTPUT.
}

// ---------------------------------------------------------
void SetupGPIOOutputPin(int pin)
{
  pinMode(pin, OUTPUT);
}
