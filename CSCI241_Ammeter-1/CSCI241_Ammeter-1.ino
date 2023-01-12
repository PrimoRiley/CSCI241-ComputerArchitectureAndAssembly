// Simulate an ammeter which has a "sample and store" capability.

#include <CSCI_Simulate_Meter.h>   // Simulate test meter utilities.
//
// A voltmeter circuit is used to measure the voltage drop across a 10
// ohm (approximately) 2-watt shunt resistor in series with the current
// source being measured.  One end of the shunt resister is always connected
// connected to Arduino ground and should be connected to the more negative
// side of the inline circuit whose current is being measured.  Using Ohm's
// law, the current flowing through the resistor can be calculated.
//
// See the "Voltmeter" program for a description of the voltmeter circuits and
// how they work.  For simplicity, the shunt voltage ADC uses the default Vcc
// (slightly less than 5.0 volts, and can fluctuate with Arduino power supply
// load) as its reference voltage. Even though this makes the current reading
// slightly less accurate (than using the internal 2.56 volt reference), it
// simplifies the shunt voltage circuit needed. For this course, the tradeoff
// is reasonable.
//
// The shunt voltmeter circuit has no voltage divider, so only currents
// from voltage sources 0.0 to 5.0 volts can be measured.  There's a 5.1 volt
// Zener diode (through 275 ohms) to ground on the analog input side of the
// shunt resistor for overvoltage protection.  There's also a 500 ma fast
// blow fuse in series with the shunt resistor to protect it from trying to
// dissipate too much heat at high currents.

/************* CALLED ONCE AT START UP *******************/
void setup()
{
  SetupAmmeter(); 
}

/******************* MAIN LOOP ***************************/

void loop() 
{
  // Depending on which type of sampling we're doing...

  switch ( SamplingType )
  {
    case RepetitiveSample:
    {
      DoRepetitiveAmmeterSample();
    }
    break;

    case BurstSample:
    {
      DoBurstSample(shuntVPin);
    }
    break;

    default:
      InternalError(__FILE__, __LINE__);
  }
}
