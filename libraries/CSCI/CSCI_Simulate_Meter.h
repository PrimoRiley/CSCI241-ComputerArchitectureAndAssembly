#ifndef INCLUDE_CSCI_SIMULATE_METER_H
#define INCLUDE_CSCI_SIMULATE_METER_H

#include <CSCI_Analog_Sample.h>

// Version text displayed when program is started.

const char MeterVersionText[] = "Version 1.0";

// Definitions for test meter simulation routines.

// Routine to do a repetitive voltmeter sample.

void DoRepetitiveVoltmeterSample();

// Routine to do a repetitive ammeter sample.

void DoRepetitiveAmmeterSample();

// Routine to do a "burst" analog sample operation.

void DoBurstSample(int analogPin);

// Display that sampled values are available.

void DisplaySampledValuesAvailable();

// Routine to initialize voltmeter components.
// Pass in the input voltage divider ratio and ADC reference voltage.

void SetupVoltmeter(double dividerRatio, double voltageRef);

// Routine to initialize ammeter components.

void SetupAmmeter();

#endif  // INCLUDE_CSCI_SIMULATE_METER_H
