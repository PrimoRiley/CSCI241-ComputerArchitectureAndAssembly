// Control a DC Motor via a GPIO port.

#include <CSCI_GPIO.h>      // Library routines
#include <CSCI_Timers.h>

const int MotorPin = 34;     // GPIO pin number motor is connected to.

const int MotorOnState = HIGH;  // State which turns motor on.
const int MotorOffState = LOW;  // State which turns motor off.

// This routine called once at program start.

void setup()
{
  SetupMotor(MotorPin);
}

// This routine called repeatedly until a "reset" is performed.

void loop ()
{
  // Number of "on/off" cycles to generate
  
  static const int numCycles = 5000;
  
  // 1000 cycles per second at 100% on.
  
  CycleMotor(MotorPin, numCycles, 1000, 0);

  // 1000 cycles per second at 75% on.

  CycleMotor(MotorPin, numCycles, 750, 250);

  // 1000 cycles per second at 50% on.

  CycleMotor(MotorPin, numCycles, 500, 500);  

  // Make sure motor is stopped.

  SetMotorState(MotorPin, MotorOffState);

  // Now wait until "reset" is pressed.

  while ( true )
  { }
}

// Routine to cycle the motor on, then off for a specific
// number of times.

void CycleMotor(int motorPin, uint32_t numTimes,
                uint32_t onTime, uint32_t offTime)
{
  for ( uint32_t count = 1; count <= numTimes; count++ )
  {
    SwitchMotorOnOff(motorPin, onTime, offTime);
  }
}

// Routine to switch motor on for the specified time, then off
// for the specified time.  Times are in microseconds.

void SwitchMotorOnOff(int motorPin, uint32_t onTime, uint32_t offTime)
{
  // Don't set state if time is zero.

  if ( onTime > 0 )
  {
    SetMotorState(motorPin, MotorOnState);
    WaitMicros(onTime);
  }

  if ( offTime > 0 )
  {
    SetMotorState(motorPin, MotorOffState);
    WaitMicros(offTime);
  }
}

// Routine to set the motor state (HIGH/LOW).

void SetMotorState(int motorPin, int state)
{
  SetGPIOOutputState(motorPin, state);
}

// Routine to setup the motor connected to the passed GPIO pin.

void SetupMotor(int motorPin)
{
  SetupGPIOOutputPin(motorPin); // Setup GPIO pin for output.  
}
