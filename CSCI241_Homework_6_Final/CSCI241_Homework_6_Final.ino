// Author: Riley Primeau
// Description: Homework #6 - Count milliseconds between pushbutton transitions.

// Place your assembly language code in one or more *.S files in the same
// folder as this program.

extern "C"
{
  // External assembly language subroutines called from C code.

  // Assembly language setup code.

  void Setup_Assembly();

  // Routine to retrieve number of milliseconds between
  // Pushbutton "B" transitions.  Sampling doesn't begin until a
  // HIGH to LOW transition occurs.  Sampling continues until either
  // Pushbutton "A" goes" LOW, or "maxTimeValues" transitions have occurred.

  uint16_t SampleButtonTransitions(uint16_t timeMillis[], uint16_t maxTimeValues);
};

// CSCI utility library includes

#include <CSCI_Console.h>
#include <CSCI_SysUtils.h>
#include <CSCI_Timers.h>

// Max number of pushbutton transition times to retain

const uint16_t MaxTransitions = 10;

// Allocate global array to hold transition times.

uint16_t TransitionTimes[MaxTransitions] = { 0 };

// Put your setup code here.  Runs once at power up or reset.

void setup()
{
  ConsoleSetup();     // Setup the user's console device.
  Setup_Assembly();   // Setup assembly language code.

  // If the Serial Monitor is running and we upload this program to the Arduino,
  // The program will start running and then the Serial Monitor will "reset"
  // the machine about 100 ms later, which will start the program running again.
  // If the program is producing sound from a buzzer, there will be a short (100 ms)
  // "beep" which is undesirable.  Wait a second before continuing the program so
  // the spurious beep won't occur.

  WaitMillis(1000);
}

// Put your main code here, which is run repeatedly.

void loop()
{
  // Inform user what to do.

  DisplayNewline();
  DisplayString("Press and release Pushbutton 'B' multiple times");
  DisplayNewline();
  DisplayString("to collect times between transitions.");
  DisplayNewline();
  DisplayNewline();
  DisplayString("Collecting ends when Pushbutton 'A' is clicked,");
  DisplayNewline();
  DisplayString("or when ");
  DisplayInteger(MaxTransitions);
  DisplayString(" transitions have occurred.");
  DisplayNewline();
  DisplayNewline();

  // Call assembly code to wait for PushButtonA to go LOW, stabalize,
  // then go HIGH and then fill the passed array with input port states.

  uint16_t numTransitions = SampleButtonTransitions(TransitionTimes, MaxTransitions);

  // Display the sample transition times.

  for ( uint16_t index = 0; index < numTransitions; index++ )
  {
    DisplayString("Time[");
    DisplayInteger(index);
    DisplayString("] = ");
    DisplayInteger(TransitionTimes[index]);
    DisplayNewline();
  }

  // Call library routine to "halt" program.

  HaltProgram();
}
