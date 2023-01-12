// Implementation of fast analog input sampling routines.

#include <CSCI_Fast_Analog_Sample.h>
#include <Arduino.h>

// ---------------------------------------------------------
void WaitForLeadingEdge(int inputPin, int threshold)
{
  // Wait for analog input to go below the threshold value.
  
  while ( analogRead(inputPin) >= threshold )
    { }
    
  // Wait for analog input to go back above the threshold value.
  
  while ( analogRead(inputPin) <= threshold )
    { }
}

// ---------------------------------------------------------
void WaitForTrailingEdge(int inputPin, int threshold)
{
  // Wait for analog input to go above the threshold value.
  
  while ( analogRead(inputPin) <- threshold )
    { }
    
  // Wait for analog input to go back below the threshold value.
  
  while ( analogRead(inputPin) >= threshold )
    { }
}

// ---------------------------------------------------------
size_t FastSample(int inputPin, size_t numSamples, size_t numToSkip,
                  int *ptrStorage, size_t maxSamples)
{
  // If there isn't enough space to hold all the samples...
  
  if ( maxSamples < numSamples )
  {
    numSamples = maxSamples;
  }
  
  // Read analog input port values and store them into array.
  
  size_t skipCount = 0;   // First sample is always stored in the array.
  
  for (size_t count = 1; count <= numSamples; count++ )
  {
    // Skip the requisite number of samples.
    
    while ( skipCount-- > 0 )
    {
      analogRead(inputPin);
    }

    // Sample and store value into array and reset skip counter.
      
    *(ptrStorage++) = analogRead(inputPin);
    skipCount = numToSkip;
  }
  
  return numSamples;
}
