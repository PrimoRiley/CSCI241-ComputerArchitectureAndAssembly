// Implementation of system-wide utility routines.

#include <CSCI_SysUtils.h>
#include <CSCI_Console.h>

// ---------------------------------------------------------
String GetStateName(int state)
{
  if ( state == HIGH )
  {
    return String("HIGH");
  }

  if ( state == LOW )
  {
    return String("LOW");
  }

  return String("???");
}

// ---------------------------------------------------------
void InternalError(const char *sourceFile, int sourceLine)
{
  String errMsg("Internal error at line ");
  errMsg += String(sourceLine);
  errMsg += " in source file: ";
  errMsg += String(sourceFile);
  DisplayError(errMsg);
  HaltProgram();
}

// ---------------------------------------------------------
void HaltProgram()
{
  DisplayNewline();
  DisplayString("Halting Program...");
  DisplayNewline();

  // Do nothing until program restart

  while ( true )
    { }
}
