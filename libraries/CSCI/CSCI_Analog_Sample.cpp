// Implementation of sample analog values routines.

#include <CSCI_Analog_Sample.h>
#include <CSCI_Fast_Analog_Sample.h>  // Fast analog sampling utilities
#include <CSCI_Console.h>             // Console utilities
#include <CSCI_PushButton.h>          // Pushbutton utilities
#include <CSCI_Timers.h>              // Timer utilities.

static String IDMessage;

static double VoltageRatio;

static double VoltageRef;

static int RawSamples[MaxSamples] CSCI_NOINIT;

static int NumRawSamples CSCI_NOINIT;

static uint32_t SampleDisplayCount CSCI_NOINIT;

static enum SampleUnits SamplingUnits = 0;  // Set by initialization routine.

static enum SampleType SamplingType CSCI_NOINIT;

static uint16_t HaveSamplesFlag CSCI_NOINIT;

// ---------------------------------------------------------
void SetupSamplingType()
{
  // Depending on the last sampling type used...

  switch ( SamplingType )
  {
    case RepetitiveSample:
      break;    // Continue doing repetitive sampling.

    case BurstSample:
    {
      // If there are valid sampled values stored...
    
      if ( HaveSamplesFlag == HaveSampledValues )
      {
        // Beep buzzer once to indicate we have valid sampled voltages.
        // Beep buzzer twice to indicate we have valid sampled currents.
        
        size_t numBeeps = 0;
        
        switch ( SamplingUnits )
        {
          case SingleVoltage:
          {
            numBeeps = 1;
          }
          break;
          
          case ShuntVoltage:
          {
            numBeeps = 2;
          }
          break;
          
          default:
            InternalError(__FILE__, __LINE__);
        }
    
        for ( size_t beeps = 1; beeps <= numBeeps; beeps++ )
        {
          digitalWrite(BuzzerPin, HIGH);
          WaitMillis(BeepInterval);
          digitalWrite(BuzzerPin, LOW);
          WaitMillis(BeepInterval);
        }
        
        // Silently wait for a button click.
        // Button 'A' means discard the sampled data.
        // Button 'B' means scroll through the sampled data.
          
        int buttonClicked = WaitForEitherButtonClick(ButtonAPin, ButtonBPin);
        
        if ( buttonClicked == ButtonAPin )
        {
          HaveSamplesFlag = ~HaveSamplesFlag;     // Indicate no valid sampled data stored.
          SamplingType = PromptForSamplingType(); // Prompt for a new sampling type.
        }
        else
        {
          // Allow user to scroll through sampled values.
          // This call never returns.
          
          ScrollSampledValues(SamplingUnits);
        }   
      }
      else
      {
        // No valid data samples, so prompt for a new sampling mode.
        
        SamplingType = PromptForSamplingType();      
      }
    }
    break;

    // Here on a power-up reset and no last sampling type is available,
    // so prompt for a sampling type.
    
    Prompt:
    default:
    {
      SamplingType = PromptForSamplingType();
    }
  }
}

// ---------------------------------------------------------
enum SampleType PromptForSamplingType()
{
  // Display ID message so user knows what program they're running.
  
  DisplayNewline();
  DisplayString(IDMessage);
  DisplayNewline();
  
  // Reset display sample counter.

  SampleDisplayCount = 1; 
  
  // Prompt for type of sampling to do.

  DisplayNewline();
  DisplayString("Click button 'A' to repetitively display samples.");
  DisplayNewline();
  DisplayString("Click button 'B' to take a burst of samples.");
  DisplayNewline();

  int buttonClicked = WaitForEitherButtonClick(ButtonAPin, ButtonBPin);

  if ( buttonClicked == ButtonAPin )
  {
    return RepetitiveSample;
  }
  else
  {
    return BurstSample;
  } 
}

// ---------------------------------------------------------
size_t PromptForAndCollectAnalogBurstSample(int analogPin)
{
  uint32_t microsPerSample = MicrosPerAnalogSample(analogPin);
  
  size_t numSamplesToKeep;
  size_t numSamplesToIgnore;
  
  PromptForBurstSample
    (microsPerSample, analogPin, numSamplesToKeep, numSamplesToIgnore);

  // Collect all the samples...

  size_t numSamples = MaxSamples;
  
  numSamples = FastSample(analogPin, numSamplesToKeep,
                          numSamplesToIgnore, RawSamples, MaxSamples);
                          
  DisplayNewline();
  DisplayString("Sampling completed!");
  DisplayNewline();

  return numSamples;
}

// ---------------------------------------------------------
void PromptForBurstSample(uint32_t microsPerSample, int edgeVoltagePin,
                          size_t& numSamplesToKeep, size_t& numSamplesToIgnore)
{
  DisplayNewline();
  DisplayString("Sample time is ");
  DisplayInteger(microsPerSample);
  DisplayString(" microseconds per sample.");
  DisplayNewline();
  DisplayString("Enter number of samples to ignore before keeping one: ");

  String inputText = KeyboardGetline();
  numSamplesToIgnore = inputText.toInt();
  
  DisplayNewline();
  DisplayString("Ignoring ");
  DisplayInteger(numSamplesToIgnore);
  DisplayString(" samples before keeping one.");
  DisplayNewline();

  DisplayNewline();
  DisplayString("You can keep up to ");
  DisplayInteger(MaxSamples);
  DisplayString(" samples.");

  numSamplesToKeep = 0;

  while ( true )
  {
    DisplayNewline();
    DisplayString("Enter number of samples to keep: ");
    
    inputText = KeyboardGetline();
    numSamplesToKeep = inputText.toInt();

    if ( numSamplesToKeep >= NumFrameSamples )
    {
      break; 
    }

    DisplayNewline();
    DisplayString("You must keep at least ");
    DisplayInteger(NumFrameSamples);
    DisplayString(" samples!");
    DisplayNewline();    
  }

  uint32_t microsPerKeptSample = ( numSamplesToIgnore + 1 ) * microsPerSample;

  double totalSampleTime =
    (double) ( microsPerKeptSample * numSamplesToKeep ) / MICROS_PER_SECOND;
 
  DisplayNewline();
  DisplayString("Your ");
  DisplayInteger(numSamplesToKeep);
  DisplayString(" samples will be ");
  DisplayInteger(microsPerKeptSample);
  DisplayString(" microseconds apart.");
  DisplayNewline();
  DisplayString("Total sampling time = ");
  DisplayDouble(totalSampleTime, 3);
  DisplayString(" seconds.");
  DisplayNewline();
  

  DisplayNewline();
  DisplayString("Click button 'A' to begin sampling after elapsed time.");
  DisplayNewline();
  DisplayString("Click button 'B' to begin sampling on edge transition.");
  DisplayNewline();

  int buttonClicked = WaitForEitherButtonClick(ButtonAPin, ButtonBPin);

  if ( buttonClicked == ButtonAPin )
  {
    DisplayNewline();
    DisplayString("Enter number of milliseconds to wait: ");

    String inputText = KeyboardGetline();
    size_t millisToWait = inputText.toInt();
  
    DisplayNewline();
    DisplayString("Press button 'A'. ");
    DisplayInteger(millisToWait);
    DisplayString(" millisecond interval begins when button is released.");
    DisplayNewline();

    WaitForButtonClick(ButtonAPin);

    WaitMillis(millisToWait);
  }
  else
  {
    DisplayNewline();
    DisplayString("Click button 'A' to begin on trailing edge.");
    DisplayNewline();
    DisplayString("Click button 'B' to begin on leading edge.");
    DisplayNewline();
  
    int triggerAmount = ( adcMaxValue - adcMinValue ) / 16;
  
    int buttonClicked = WaitForEitherButtonClick(ButtonAPin, ButtonBPin);
  
    if ( buttonClicked == ButtonAPin )
    {
      WaitForTrailingEdge(edgeVoltagePin, adcMaxValue - triggerAmount );
    }
    else
    {
      WaitForLeadingEdge(edgeVoltagePin, adcMinValue + triggerAmount );
    }
  }  
}

// ---------------------------------------------------------
void ScrollSampledValues(enum SampleUnits units)
{
  // Number of samples available.

  int numSamples = NumRawSamples;

  // Start with first sample.

  int sample_pos = 0;

  while ( true )
  {
    int buttonClicked = WaitForEitherButtonClick(ButtonAPin, ButtonBPin);

    // If we are to scroll forward through the data.
    
    if ( buttonClicked == ButtonBPin )
    {
      // If beyond available data...
      
      if ( sample_pos >= numSamples )
      {
        // Position one frame from the end of the data.
        
        sample_pos = numSamples - NumFrameSamples;
      }
            
      // Display current data frame.
      
      DisplaySampledValues(units, sample_pos, NumFrameSamples, numSamples);
      sample_pos += NumFrameSamples;  // Advance to next data frame. 
    }
    else
    {
      // Scroll reverse through the data.
      // Move back over this data frame, plus one more.

      sample_pos -= (2 * NumFrameSamples); 

      // If we're before the beginning of the data...
      
      if ( sample_pos < 0 )
      {
        sample_pos = 0;   // Start at beginning of the data.
      }
      
      DisplaySampledValues(units, sample_pos, NumFrameSamples, numSamples);
      sample_pos += NumFrameSamples;  // Advance to next data frame.                                 
    }
  }
}

// ---------------------------------------------------------
void DisplaySampledValues(enum SampleUnits units, size_t begPos,
                          size_t numValues, size_t numSamples)
{
  double voltage = 0.0;   // Holds voltage samples.

  // Init sample counter.

  SampleDisplayCount = begPos + 1;
  
  for ( size_t i = 0; i < numValues; i++ )
  {
    // If value is in the samples array...

    size_t pos = begPos + i;

    if ( pos < numSamples )
    {
      switch ( units )
      {
        case SingleVoltage:
        {
          voltage = AnalogInputToVoltage(RawSamples[pos]);
          DisplaySampleVoltage(voltage);
        }
        break;
        
        case ShuntVoltage:
        {
          voltage = AnalogShuntToVoltage(RawSamples[pos]);
          DisplaySampleCurrent(voltage);
        }
        break;
        
        default:
          InternalError(__FILE__, __LINE__);
      }
    }
  }
}

// ---------------------------------------------------------
void DisplaySampleVoltage(double voltage)
{
  // Display the measured sample voltage.

  DisplayString("Voltage[");
  DisplayInteger(SampleDisplayCount);
  DisplayString("]:");
  DisplayDouble(voltage, 2);  // Second parameter is digits after "."
  DisplayNewline();

  SampleDisplayCount++;
}

// ---------------------------------------------------------
void DisplaySampleCurrent(double shuntVoltage)
{
  // Display the measured sample current (in milliamps).
  
  double current = ( shuntVoltage / shuntResistance ) * 1000.0;
  
  // *** Start of TEST ***

  /*
  if ( current > 12.0 )
  {
    DisplayNewline();
    DisplayString("current = ");
    DisplayDouble(current, 2);
    DisplayNewline();
    DisplayPause();
  }
  */
  
  // *** End of TEST ***

  DisplayString("Current[");
  DisplayInteger(SampleDisplayCount);
  DisplayString("](ma):");
  DisplayDouble(current, 2);  // Second parameter is digits after "."
  DisplayNewline();

  SampleDisplayCount++;
}

// ---------------------------------------------------------
double AverageVoltage(int voltagePin, size_t numSamples)
{
  double sumVoltages = 0.0;

  // Sample the analog input pin the specified number of times.

  numSamples = FastSample(voltagePin, numSamples, 0, RawSamples, MaxSamples);

  for ( size_t index = 0; index < numSamples; index++ )
  {
    sumVoltages += AnalogInputToVoltage(RawSamples[index]);
  }

  return sumVoltages / numSamples;
}

// ---------------------------------------------------------
double AverageShuntVoltage(int shuntVPin, size_t numSamples)
{
  double sumVoltages = 0.0;

  // Sample the analog input pin the specified number of times.

  numSamples = FastSample(shuntVPin, numSamples, 0, RawSamples, MaxSamples);

  for ( size_t index = 0; index < numSamples; index++ )
  {
    sumVoltages += AnalogShuntToVoltage(RawSamples[index]);
  }

  return sumVoltages / numSamples;
}

// ---------------------------------------------------------
uint32_t MicrosPerAnalogSample(int analogPin)
{
  uint32_t upTime = micros();   // Get system uptime in microseconds.

  // Take as many samples as possible as fast as possible.

  size_t numSamples = FastSample(analogPin, MaxSamples, 0, RawSamples, MaxSamples);

  uint32_t elapsedTime = micros() - upTime;

  return (elapsedTime / numSamples);
}

// ---------------------------------------------------------
double AnalogInputToVoltage(int inputValue)
{
  // Calculate fraction of total range.
  
  double rangeFraction = (double) (inputValue - adcMinValue) /
                         (double) (adcMaxValue - adcMinValue);
                         
  // Calculate maximum voltage we can measure.

  double maxVoltage = VoltageRef * VoltageRatio;

  // Determine actual voltage being measured.

  double voltage = maxVoltage * rangeFraction;

  return voltage;  
}

// ---------------------------------------------------------
double AnalogShuntToVoltage(int inputValue)
{
  // Calculate fraction of total range.
  
  double rangeFraction = (double) (inputValue - adcMinValue) /
                         (double) (adcMaxValue - adcMinValue);
                         
  // Calculate maximum voltage shunt ADC can measure.

  double maxVoltage = shuntVRef;

  // Determine actual voltage being measured.

  double voltage = maxVoltage * rangeFraction;

  return voltage;  
}
