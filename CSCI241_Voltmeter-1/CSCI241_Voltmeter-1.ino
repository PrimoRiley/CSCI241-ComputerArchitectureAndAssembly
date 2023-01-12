// Simulate a voltmeter which has a "sample and store" capability.

#include <CSCI_Simulate_Meter.h>   // Simulate test meter utilities.

// An (approximately) 11:1 voltage divider (931K : 95.3K) is connected to
// an Arduino analog GPIO input pin.  The ADC converter is set to use
// the internal constant 2.56 volt reference source when doing ADC
// conversions. The ADC divides the 0.0 to 2.56 volt range into 1023
// equally spaced integer intervals. This means an input voltage in the
// range 0.0 to 28.2 (11 x 2.56) volts can be measured to an approximate
// accuracy of 0.027 (28.2 / 1023) volts (or 27.5 millivolts).  This is
// good enough for the type of work done in this course.  It also allows
// measuring most DC voltages encountered in this course without having
// to switch measurement scales.

// The Arduino analog GPIO pin has a maximum rated input voltage of 5.5
// volts.  Because of the voltage divider, it would require the voltmeter
// input to be connected to a 60.5 (5.5 x 11) volt source before damage
// to the Arduino would occur.  Even though this is unlikely, a 5.1 volt
// Zener diode is connected between the GPIO pin and ground.  Should the
// input voltage exceed 56.1 (5.1 x 11), the Zener diode will clamp the
// GPIO pin voltage to 5.1 volts, providing overvoltage protection.
// The Zener diode also protects against negative input voltages (which
// can also damage the GPIO pin if excessive).  If a negative input
// voltage is applied, the Zener diode will clamp to -0.7 volts, which
// won't damage the Arduino.

/************* CALLED ONCE AT START UP *******************/
void setup()
{
  // Voltage divider ratio specific to resistors on the utility breadboard.
  
  const double VOLTAGE_DIVIDER_RATIO = 11.219;

  // ADC voltage reference, as measured at the Arduino AREF pin.
  
  const double ADC_VOLTAGE_REFERENCE = 2.56;
  
  SetupVoltmeter(VOLTAGE_DIVIDER_RATIO, ADC_VOLTAGE_REFERENCE);
}

/******************* MAIN LOOP ***************************/

void loop() 
{
  // Depending on which type of sampling we're doing...

  switch ( SamplingType )
  {
    case RepetitiveSample:
    {
      DoRepetitiveVoltmeterSample();
    }
    break;

    case BurstSample:
    {
      DoBurstSample(voltagePin);
    }
    break;

    default:
    {
      InternalError(__FILE__, __LINE__);
    }
  }
}
