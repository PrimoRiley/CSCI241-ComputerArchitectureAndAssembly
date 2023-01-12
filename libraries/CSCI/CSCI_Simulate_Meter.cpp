// Implementation of test meter simulation routines.

#include <CSCI_Simulate_Meter.h>
#include <CSCI_Console.h>     // Console utilities
#include <CSCI_PushButton.h>  // Pushbutton utilities
#include <CSCI_Timers.h>      // Timer utilities

// ---------------------------------------------------------
void DoRepetitiveVoltmeterSample()
{
  // If button 'A' NOT pressed...

  if ( !IsButtonPressed(ButtonAPin) )
  {
    const size_t numSamples = 10;  // Number of samples to average.

    double avgVoltage = AverageVoltage(voltagePin, numSamples);

    // Display the measured average voltage.
        
    DisplaySampleVoltage(avgVoltage);

    WaitMillis(sampleDelay);
  }
  else
  {
    // Wait for button release, then prompt user for new sampling type.

    WaitForButtonRelease(ButtonAPin);
    SamplingType = PromptForSamplingType();
  }
}

// ---------------------------------------------------------
void DoRepetitiveAmmeterSample()
{
  // If button 'A' NOT pressed...

  if ( !IsButtonPressed(ButtonAPin) )
  {
    const size_t numSamples = 10;  // Number of samples to average.

    double avgDiffVoltage = AverageShuntVoltage(shuntVPin, numSamples);

    // Display the measured average current.
        
    DisplaySampleCurrent(avgDiffVoltage);

    WaitMillis(sampleDelay);
  }
  else
  {
    // Wait for button release, then prompt user for new sampling type.

    WaitForButtonRelease(ButtonAPin);
    SamplingType = PromptForSamplingType();
  }
}

// ---------------------------------------------------------
void DoBurstSample(int analogPin)
{
  NumRawSamples = PromptForAndCollectAnalogBurstSample(analogPin);

  DisplaySampledValuesAvailable();
}

// ---------------------------------------------------------
void DisplaySampledValuesAvailable()
{
  // Indicate sampled values are available and valid.

  HaveSamplesFlag = HaveSampledValues;

  DisplayNewline();
  DisplayString("Click button 'A' to discard samples taken.");
  DisplayNewline();
  DisplayString("Click button 'B' (or open the Plot Monitor) to view samples taken.");
  DisplayNewline();
  DisplayString("[When viewing, button 'B' scrolls forward, 'A' scrolls backward.]");
  DisplayNewline();
  DisplayNewline();
  DisplayString("Note: If you open the Plot Monitor, a 'soft reset' will occur and");
  DisplayNewline();
  DisplayString("      the program will beep and pause.  You can then click button 'B'");
  DisplayNewline();
  DisplayString("      to view the values, or click button 'A' to discard them.");
  DisplayNewline();
  
  int buttonClicked = WaitForEitherButtonClick(ButtonAPin, ButtonBPin);

  if ( buttonClicked == ButtonAPin )
  {
    HaveSamplesFlag = ~HaveSamplesFlag;     // Indicate no valid samples.
    SamplingType = PromptForSamplingType(); // Prompt for a new sampling type.
  }
  else
  {
    // Allow user to scroll through the stored values in the Serial Monitor
    // window. If user closes the Serial Monitor and opens the Serial Plotter,
    // a "soft reset" will occur and the program will restart.  Logic in the
    // "setup" routine will detect the presense of stored data and allow the
    // user to scroll through it.

    ScrollSampledValues(SamplingUnits); // This routine does not return.
  }
}

// ---------------------------------------------------------
void SetupVoltmeter(double dividerRatio, double voltageRef)
{
  pinMode(voltagePin, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  
  // Note:  This course uses the Arduino Mega.  Only the Arduino
  //        Mega has a 2.56 volt internal ADC reference voltage.
  //        If you're using an Arduino Uno, then change INTERNAL2V56
  //        to INTERNAL.  This will use the Uno's internal 1.1 volt
  //        ADC reference.  You must then measure the voltage on the
  //        Uno's AREF pin and change the voltageRef constant above.
  //
  //        This means the maximum voltage you can measure with
  //        an Arduino Uno is 12.1 (11 x 1.1) volts.  If you want to
  //        measure larger voltages with an Uno, you'll have to
  //        change the voltage divider resistance values so the
  //        voltageRatio value is larger.
    
  analogReference(INTERNAL2V56);  // Use internal "2.56" volt ADC reference.
  
  VoltageRatio = dividerRatio;    // Store voltage divider ratio for later use.
  VoltageRef = voltageRef;        // Store actual voltage reference value for later use.
  
  ConsoleSetup();
  
  // Construct identification message to be displayed at program (re)start.
  
  IDMessage = "Voltmeter - ";
  IDMessage += MeterVersionText;
  
  // Set the sample measurement units.
  
  SamplingUnits = SingleVoltage;
  
  // Determine which type of sampling to do.

  SetupSamplingType();
}

// ---------------------------------------------------------
void SetupAmmeter()
{
  pinMode(shuntVPin, INPUT);
  pinMode(BuzzerPin, OUTPUT);  

  // Use Vcc (approx 5.0 volts) as the ADC reference voltage.
  // This means each of the voltmeters can measure a voltage
  // change of .0049 (5.0 / 1023) volts.  A voltage drop of
  // this amount across 10 ohms is .00049 amps (0.49 ma).
    
  analogReference(DEFAULT);   // Use Vcc (approx 5.0 volts)
  
  ConsoleSetup();
  
  // Construct identification message to be displayed at program (re)start.
  
  IDMessage = "Ammeter - ";
  IDMessage += MeterVersionText; 
  
  // Set the sample measurement units.
  
  SamplingUnits = ShuntVoltage;   

  // Determine which type of sampling to do.

  SetupSamplingType();
}


