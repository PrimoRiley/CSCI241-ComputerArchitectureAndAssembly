// Display using an 8-segment LED module.

#include <CSCI_LED.h>    // Library routines
#include <CSCI_Timers.h>

// IMPORTANT: The GPIO pin numbers (29,28,...,23,22) connected to each LED module segment
//            were purposely chosen to correspond to the 8 GPIO pins associated with
//            Arduino Mega PORTA.  Therefore, the following port address pointers can be
//            used to access all 8-bits at one time.

const uint8_t *PortDirPtr = &DDRA;    // Ptr to port input/output direction control bits.
const uint8_t *PortDataPtr = &PORTA;  // Ptr to port data bits.

// These are "bit masks" corresponding to the port pin controlling each LED segment.
// Note: The MSB corresponds to GPIO pin 29, while the LSB corresponds to GPIO pin 22.

const uint8_t SegAPin  = 0b00000001;  // Pin associated with the "A" (top) segment
const uint8_t SegBPin  = 0b00000010;  // Pin associated with the "B" (top right) segment
const uint8_t SegCPin  = 0b00000100;  // Pin associated with the "C" (bottom right) segment
const uint8_t SegDPin  = 0b00001000;  // Pin associated with the "D" (bottom) segment
const uint8_t SegEPin  = 0b00010000;  // Pin associated with the "E" (bottom left) segment
const uint8_t SegFPin  = 0b00100000;  // Pin associated with the "F" (top left) segment
const uint8_t SegGPin  = 0b01000000;  // Pin associated with the "G" (middle) segment
const uint8_t SegDPPin = 0b10000000;  // Pin associated with the "DP" (decimal point)

const uint8_t SegAllPins = SegAPin | SegBPin | SegCPin | SegDPin |
                           SegEPin | SegFPin | SegGPin | SegDPPin;

// State-related definitions

const int LedOnState = HIGH;  // State which turns LED segment on.
const int LedOffState = LOW;  // State which turns LED segment off.

// In order to display a numeric digit (0,1,2,...,9), it's necessary to light one
// or more appropriate LED segments.  Which segments to light will be represented
// by 1 bits in an eight bit byte.  Here are the bit patterns representing each segment.
// (A binary 1 in that position means that segment is to be lit, a binary 0 means
// that segment is NOT to be lit.)
//
// Example: The numeric digit "1" is displayed by lighting segments "B" and "C", so
// the bits in the byte should be: (SegBPin | SegCPin)

// Each element in the following array holds the segment sequence pattern
// corresponding to each numeric digit (0,1,2,3,4,5,6,7,8,9).

const uint8_t DigitToSegSequence[] =
{
  SegAPin | SegBPin | SegCPin | SegDPin | SegEPin | SegFPin          ,  // "0"
            SegBPin | SegCPin                                        ,  // "1"
  SegAPin | SegBPin           | SegDPin | SegEPin           | SegGPin,  // "2"      
  SegAPin | SegBPin | SegCPin | SegDPin                     | SegGPin,  // "3"  
            SegBPin | SegCPin                     | SegFPin | SegGPin,  // "4"
  SegAPin           | SegCPin | SegDPin           | SegFPin | SegGPin,  // "5"
  SegAPin           | SegCPin | SegDPin | SegEPin | SegFPin | SegGPin,  // "6"              
  SegAPin | SegBPin | SegCPin                                        ,  // "7"
  SegAPin | SegBPin | SegCPin | SegDPin | SegEPin | SegFPin | SegGPin,  // "8"
  SegAPin | SegBPin | SegCPin | SegDPin           | SegFPin | SegGPin   // "9"      
};

// Note: The bit corresponding to the decimal point (DP segment) is always 0.  Whether or not
//       to set it to 0 or 1 is determined by special logic.

// Called once at start up

void setup()
{
  SetupLEDPort(PortDirPtr);   // Set port direction bits.
  SetLEDPortBits(PortDataPtr, SegAllPins, LedOffState);	// Turn all segments off.

  // Flash each segment so we know circuitry is working.

  const int holdTime = 250;   // In milliseconds.

  FlashEachSegment(PortDataPtr, holdTime);
}

// Called repeatedly until the reset button is pressed

void loop()
{
  static const int digitHoldTime = 5000;
  
  // For each decimal digit...

  for ( size_t digit = 0; digit <= 3; digit++ )
  {
    uint8_t segBits = DigitToSegSequence[digit];

    // If digit is an odd number...

    if ( digit & 1 )
    {
      segBits |= SegDPPin;  // Display the decimal point.
    }

    FlashSegments(PortDataPtr, segBits, digitHoldTime);
  }
}

// -------------------------------------------------------------------------------------
// Flash each LED segment in order (A,B,C,D,E,F,G,DP) for the indicated
// period of time for visual verification the circuitry is wired correctly.

void FlashEachSegment(uint8_t *portDataPtr, int holdTime)
{
  // Start with segment "A" and go clockwise.

  FlashSegments(portDataPtr, SegAPin, holdTime);
  FlashSegments(portDataPtr, SegBPin, holdTime);
  FlashSegments(portDataPtr, SegCPin, holdTime);
  FlashSegments(portDataPtr, SegDPin, holdTime);
  FlashSegments(portDataPtr, SegEPin, holdTime);
  FlashSegments(portDataPtr, SegFPin, holdTime);
  FlashSegments(portDataPtr, SegGPin, holdTime);

  // Flash the decimal point segment last.
  
  FlashSegments(portDataPtr, SegDPPin, holdTime);
}

// -------------------------------------------------------------------------------------
// Flash LED segments indicated by bits in "segBits" for the specified
// hold time, then turn them off for the same time.

void FlashSegments(uint8_t *portDataPtr, uint8_t segBits, int holdTime)
{
  SetLEDPortBits(portDataPtr, segBits, LedOnState);
  WaitMillis(holdTime);
  SetLEDPortBits(portDataPtr, segBits, LedOffState);
  WaitMillis(holdTime);  
}
