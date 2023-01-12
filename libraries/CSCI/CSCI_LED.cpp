// LED routines.

#include <CSCI_LED.h>
#include <CSCI_GPIO.h>
#include <CSCI_Timers.h>

// ---------------------------------------------------------
void SetLEDPortBits(uint8_t *portDataPtr, uint8_t bits, int onState)
{
  SetGPIOutputPortState(portDataPtr, bits, onState);
}

// ---------------------------------------------------------
void SetLEDByteState(uint8_t byte, const int bitToPin[8], int state)
{
  // Start at the LSB
  
  uint8_t bitMask = 0b00000001;
  
  // Check all bits, from LSB (bit 0) to MSB (bit 7)
  
  for ( uint8_t bit = 0; bit < 8; bit++ )
  {
    int pin = bitToPin[bit];
    
    if ( byte & bitMask )
    {
      // Bit is a 1, set LED to indicated state.
      
      SetLEDState(pin, state);
    }
    else
    {
      // Bit is a 0, set LED to opposite state.
      
      SetLEDState(pin, (state == HIGH) ? LOW : HIGH);
    }
    
    bitMask = bitMask << 1;   // Shift mask one position to the left.
  }
}

// ---------------------------------------------------------
void SetLEDState(int pin, int state)
{
  SetGPIOOutputState(pin, state);
}

// ---------------------------------------------------------
void SetupLEDPort(uint8_t *portDirPtr)
{
  SetupGPIOOutputPort(portDirPtr);
}

// ---------------------------------------------------------
void SetupLEDByte(const int bitToPin[8])
{
  // Setup each GPIO pin corresponding to each bit.
  
  for ( uint8_t bit = 0; bit < 8; bit++ )
  {
    SetupLED(bitToPin[bit]);
  }
}

// ---------------------------------------------------------
void SetupLED(int pin)
{
  SetupGPIOOutputPin(pin);
}
