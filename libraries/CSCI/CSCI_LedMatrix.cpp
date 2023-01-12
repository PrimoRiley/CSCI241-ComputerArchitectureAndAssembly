// Implementation of LED matrix routines

#include <CSCI_LedMatrix.h>
#include <CSCI_Timers.h>

// Construct a global LedControl object, indicating there's only
// one MAX7219 chip (which could be daisy chained to others).

LedControl LedCtl(DINPin, CLKPin, CSPin, 1);

// ---------------------------------------------------------
void SetLedRow(int row, uint8_t pattern)
{
  LedCtl.setRow(MatAddr, row, pattern);
}

// ---------------------------------------------------------
void SetLedOn(int row, int col)
{
  LedCtl.setLed(MatAddr, row, col, true);
}

// ---------------------------------------------------------
void SetLedOff(int row, int col)
{
  LedCtl.setLed(MatAddr, row, col, false);
}

// ---------------------------------------------------------
void ClearLedMatrix()
{
  LedCtl.clearDisplay(MatAddr);
}

// ---------------------------------------------------------
void SetupLedMatrix()
{
  // Make sure display is NOT in power saving mode.
  
  LedCtl.shutdown(MatAddr, false);

  // Set brightness (0 = lowest, 15 = highest) to a medium value.

  LedCtl.setIntensity(MatAddr, 8);

  ClearLedMatrix();

  // Show display is working by turning on each row in sequence.

  for ( int row = 0; row < NumMatRows; row++ )
  {
    SetLedRow(row, 0b11111111);
    WaitMillis(250); 
  }

  // Keep all rows on for brief interval.
  
  WaitMillis(1000);
  
  ClearLedMatrix();
}
