#ifndef INCLUDE_FAST_ANALOG_SAMPLE_H
#define INCLUDE_FAST_ANALOG_SAMPLE_H

#include <Arduino.h>

// Definitions related to fast analog input sampling.

// Wait for an analog input pin to trigger on a "leading" edge (LOW to
// HIGH transition).  Waits for the analog value to go below the indicated
// threshold, then waits for it to go back above the threshold.

void WaitForLeadingEdge(int inputPin, int threshold);

// Wait for an analog input pin to trigger on a "trailing" edge (HIGH to
// LOW transition).  Waits for the analog value to go above the indicated
// threshold, then waits for it to go back below the threshold.

void WaitForTrailingEdge(int inputPin, int threshold);

// Sample 16-bit raw analog values from input pin until either the number
// of samples is stored or the array size is reached.
// "numToSkip" (0,1,2,3,...) is the number of input samples to skip before
// storing a sample in the array.
// Returns the actual number of samples stored in the array.

size_t FastSample(int inputPin, size_t numSamples, size_t numToSkip,
                  int *ptrStorage, size_t maxSamples);
                  
#endif  // INCLUDE_FAST_ANALOG_SAMPLE_H
