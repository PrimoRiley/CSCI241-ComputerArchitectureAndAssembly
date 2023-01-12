// Implementation of console display and keyboard routines

#include <CSCI_Console.h>

// *************** Console I/O Routines ***************

// ---------------------------------------------------------
void ConsoleSetup()
{
  Serial.begin(38400);    // Set USB transmission speed.
}

// ---------------------------------------------------------
void DisplayInteger(int value)
{
  Serial.print(value);
}

// ---------------------------------------------------------
void DisplayInteger(uint8_t value)
{
  Serial.print(value);
}

// ---------------------------------------------------------
void DisplayInteger(uint16_t value)
{
  Serial.print(value);
}

// ---------------------------------------------------------
void DisplayInteger(int32_t value)
{
  Serial.print(value);
}

// ---------------------------------------------------------
void DisplayInteger(uint32_t value)
{
  Serial.print(value);
}

// ---------------------------------------------------------
void DisplayDouble(double value, size_t numDecimals)
{
  Serial.print(value, numDecimals);
}

// ---------------------------------------------------------
void DisplayAsBinary(char value)
{
  // Go from MSB to LSB.
  
  uint8_t mask = 0b10000000;
  
  while ( mask != 0 )
  {
    if ( value & mask )
    {
      DisplayString("1");
    }
    else
    {
      DisplayString("0");
    }
    
    mask = mask >> 1;   // Logical shift one bit to the right.
  }
}

// ---------------------------------------------------------
void DisplayAsBinary(uint8_t value)
{
  // Go from MSB to LSB.
  
  uint8_t mask = 0b10000000;
  
  while ( mask != 0 )
  {
    if ( value & mask )
    {
      DisplayString("1");
    }
    else
    {
      DisplayString("0");
    }
    
    mask = mask >> 1;   // Logical shift one bit to the right.
  }
}

// ---------------------------------------------------------
void DisplayAsBinary(uint16_t value)
{
  // Go from MSB to LSB.
  
  uint16_t mask = 0b1000000000000000;
  
  while ( mask != 0 )
  {
    if ( value & mask )
    {
      DisplayString("1");
    }
    else
    {
      DisplayString("0");
    }
    
    mask = mask >> 1;   // Logical shift one bit to the right.
  }
}

// ---------------------------------------------------------
void DisplayError(const String& errMsg)
{
  DisplayNewline();
  DisplayString("*** Error: ");
  DisplayString(errMsg);
  DisplayPause();
}

// ---------------------------------------------------------
void DisplayPause()
{
  DisplayNewline();
  DisplayString("Paused: Press 'Enter' key to continue...");
  KeyboardGetline();
  DisplayNewline();  
}

// ---------------------------------------------------------
String KeyboardGetline()
{
  // Wait until some serial input is available.

  while ( Serial.available() == 0 )
  {
    // Do nothing, keep checking.
  }

  String line = Serial.readString();

  // Strip off any newline at the end of the string.

  int num_chars = line.length();

  if ( num_chars > 0 )
  {
    if ( line.charAt(num_chars - 1) == '\n' )
    {
      line.remove(num_chars - 1);
    }
  }

  return line;
}

// ---------------------------------------------------------
void DisplayString(const String& str)
{
  Serial.print(str);
}

// ---------------------------------------------------------
void DisplayNewline()
{
  Serial.println();
}
