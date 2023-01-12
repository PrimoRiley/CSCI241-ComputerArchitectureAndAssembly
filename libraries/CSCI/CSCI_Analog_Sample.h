#ifndef INCLUDE_CSCI_ANALOG_SAMPLE_H
#define INCLUDE_CSCI_ANALOG_SAMPLE_H

#include <Arduino.h>
#include <CSCI_SysUtils.h>    // System utilities

// Holds identification message displayed when program is restarted.

extern String IDMessage;

const int voltagePin = A15;   // Analog GPIO pin measuring input voltage.

// Analog GPIO pin connected to non-grounded end of the shunt resistor.

const int shuntVPin = A14;

// Two pushbuttons control the operation of the meter.
// Clicking button "A" displays repeated averaged samples.
// Clicking button "B" fast samples a group of values, storing them
// in RAM, then allows one to scroll through displaying the values.

const int ButtonAPin = 52;
const int ButtonBPin = 53;

// Active buzzer (for alert sounds) is connected to this GPIO pin.

const int BuzzerPin = 51;

const int BeepInterval = 500;   // Beep interval (in milliseconds)

// Some analog to digital converter input constants

const int adcMinValue = 0;    // Analog input minimum value.
const int adcMaxValue = 1023; // Analog input maximum value.

// *** IMPORTANT ***
//
// Even though the theoretical value of the internal constant ADC
// reference voltage is 2.56 volts, the following holds the actual value
// as measured at the AREF pin while this program is running.  This
// measurement only needs to be taken once.  Must be initialized before use!

extern double VoltageRef;

// *** IMPORTANT ***
//
// For our purposes, assume the ammeter ADC reference voltage (Vcc) is
// the following value.  Unfortunately, Vcc fluctuates with Arduino power
// supply load, so the current calculated may not be as precise as it could
// be.  I've decided this is good enough for this course.  This also
// simplifies the ammeter circuitry.

const double shuntVRef = 5.00;

// *** IMPORTANT ***
//
// The following holds the actual voltage divider ratio as determined
// by a one-time measurement.  This value doesn't change unless the
// voltage divider resistor values change. Must be initialized before use!

extern double VoltageRatio;

// *** IMPORTANT ***
//
// The following is the actual resistance (in ohms) of the shunt in series
// with the current source.  This is determined via a one-time measurement.

const double shuntResistance = 10.2;

// Array to hold raw 10-bit analog input sample values.
// Since this array is allocated in Arduino dynamic memory, the Uno
// can conservatively hold about 500 values and the Mega about 2000.
//
// Note: The array contents are purposely NOT initialized at "reset" time
//       so that sampled data may be retained across resets (if desired).

const int MaxSamples = 2000;

extern int RawSamples[MaxSamples] CSCI_NOINIT;

// Holds number of raw samples stored in the array.  Purposely NOT initialized
// at "reset" time so any sampled data can be retained (if desired).

extern int NumRawSamples CSCI_NOINIT;

// Sample display counter.  Starts at 1 when we begin displaying samples
// and gets incremented each time a sample is displayed.

extern uint32_t SampleDisplayCount CSCI_NOINIT;

// Number of samples in each Arduino Plot Monitor display "frame".
// This is the number of samples displayed on the Plot Monitor's
// horizontal axis.

const int NumFrameSamples = 500;

// Delay (in milliseconds) between each repetitive sample.

const int sampleDelay = 20;

// Measurement units sample values represent.

enum SampleUnits
{
  SingleVoltage = 1,    // Single voltage value.
  ShuntVoltage = 2      // Voltage across shunt resistor. 
};

// Holds the sample measurement units.

extern enum SampleUnits SamplingUnits;

// The types of sampling we can do.

enum SampleType
{
  Prompt = 0,             // Prompt user for new sampling type.
  RepetitiveSample = 1,   // Repetitive slow sampling.
  BurstSample = 2         // Burst mode stored sampling.
};

// Holds the type of sampling to be performed.  This value is purposely NOT
// initialized at "reset" time.  A power-on reset will result in the value
// containing "garbage" bits.  A "soft" reset (RESET button press or opening
// either the Serial Monitor or Serial Plotter windows) will retain the value
// from the previous run of the program.

extern enum SampleType SamplingType CSCI_NOINIT;

// The "HaveSamplesFlag" is purposely not initialized at "reset" time.
// The variable is set to "HaveSampledValues" bit pattern if there are
// valid samples stored in the "RawSamples" array (and "NumRawSamples" is
// also assumed to be valid).  The "HaveSampledValues" bit pattern is chosen
// so it's extremely unlikely a power-on "reset" will result in the
// "HaveSamplesFlag" bits to power on to the "HaveSampledValues" bit pattern.
// So, a power-on reset will assume there are no sampled values retained.

const uint16_t HaveSampledValues = 0b1010101010101010;

extern uint16_t HaveSamplesFlag CSCI_NOINIT;

// Routine to determine type of sampling to do.

void SetupSamplingType();

// Routine to prompt for sampling type to do.  Returns one
// of the SampleType enumerations.

enum SampleType PromptForSamplingType();

// Routine to prompt for and collect an analog burst sample.
// Returns the number of samples kept.

size_t PromptForAndCollectAnalogBurstSample(int analogPin);

// Routine to prompt for burst sample parameters.

void PromptForBurstSample(uint32_t microsPerSample, int edgeVoltagePin,
                          size_t& numSamplesToKeep, size_t& numSamplesToIgnore);

// Routine to allow user to scroll back and forth displaying the
// sampled values.  This routine does NOT return!

void ScrollSampledValues(enum SampleUnits units);

// Routine to display the specified number of sampled values
// beginning at the specified position in the samples array.
// "numSamples" is the number of samples in the array.

void DisplaySampledValues(enum SampleUnits units, size_t begPos,
                          size_t numValues, size_t numSamples);

// Routine to display a sampled voltage value.

void DisplaySampleVoltage(double voltage);

// Routine to display a sampled current value given shunt voltage difference.

void DisplaySampleCurrent(double shuntVoltage);

// Function to sample an analog voltage a specified number of times and
// return the the average of those samples.

double AverageVoltage(int voltagePin, size_t numSamples);

// Function to sample shunt analog voltage a specified number of times
// and return the the average of those samples.

double AverageShuntVoltage(int shuntVPin, size_t numSamples);

// Function to return the number of microseconds per analog sample.

uint32_t MicrosPerAnalogSample(int analogPin);

// Function to take a raw analog voltage input pin value and return the
// voltage associated with that value.

double AnalogInputToVoltage(int inputValue);

// Function to take a raw analog shunt input value and return the
// voltage associated with that value.

double AnalogShuntToVoltage(int inputValue);

#endif  // INCLUDE_CSCI_ANALOG_SAMPLE_H
