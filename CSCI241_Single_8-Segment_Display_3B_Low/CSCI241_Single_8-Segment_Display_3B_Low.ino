// Display using an 8-segment LED module. (Homework)

#include <CSCI_LED.h>    // Library routines
#include <CSCI_Timers.h>

const int SegAPin = 22;  // Output pin associated with the "A" (top) segment
const int SegBPin = 23;  // Output pin associated with the "B" (top right) segment
const int SegCPin = 24;  // Output pin associated with the "C" (bottom right) segment
const int SegDPin = 25;  // Output pin associated with the "D" (bottom) segment
const int SegEPin = 26;  // Output pin associated with the "E" (bottom left) segment
const int SegFPin = 27;  // Output pin associated with the "F" (top left) segment
const int SegGPin = 28;  // Output pin associated with the "G" (middle) segment
const int SegDPPin = 29; // Output pin associated with the "DP" (decimal point)

// IMPORTANT: The pin numbers above were purposely chosen to correspond to the 8 GPIO pins
//            associated with Arduino Mega PORTA.  Therefore, the following port address
//            pointers can be used to access all 8-bits at one time.

uint8_t *PortDirPtr = &DDRA;    // Ptr to port input/output direction control bits.
uint8_t *PortDataPtr = &PORTA;  // Ptr to port data bits.

// State-related definitions

const int LedOnState = LOW;  // State which turns LED segment on.
const int LedOffState = HIGH;  // State which turns LED segment off.

// In order to display a numeric digit (0,1,2,...,9), it's necessary to light one
// or more appropriate LED segments.  Which segments to light will be represented
// by 0 bits in an eight bit byte.  Here are the bit positions (MSB on left, LSB on right)
// representing each segment.  (A binary 0 in that position means that segment is
// to be lit, a binary 1 means that segment is NOT to be lit.)
//
// DP G F E D C B A   ("DP" is a single bit representing the decimal point segment)

// Each element in the following array holds the segment sequence pattern
// corresponding to each numeric digit (0,1,2,3,4,5,6,7,8,9).

const uint8_t DigitToSegSequence[] =
{
  0b00111111,   // "0"
  0b10000110,   // "1"
  0b01011011, //2
  0b11001111, //3
  0b01100110, //4
  0b11101101, //5
  0b01111101, //6
  0b10000111, //7
  0b01111111, //8
  0b11101111    // "9"
};

const uint8_t segment[] =
{
  0b00000001, //A
  0b00000010, //B
  0b00000100, //C
  0b00001000, //D
  0b00010000, //E
  0b00100000, //F
  0b01000000, //G
  0b10000000, //DP
};

// Called once at start up

void setup()
{
  // Set port direction bits to output. 
  SetupLEDPort(PortDirPtr);
  SetLEDPortBits(PortDataPtr, 0b11111111, 1);
  // Flash each segment so we know circuitry is working.
  for (int i = 0; i <= 7; i++)
  {
    SetLEDPortBits(PortDataPtr, segment[i], 0);
    delay(250);
    SetLEDPortBits(PortDataPtr, segment[i], 1);
  }
}

// Called repeatedly until the reset button is pressed

void loop()
{
  static const int digitHoldTime = 1000;	// Time in milliseconds

  // For each decimal digit (0,1,2,...,9), display the digit on for "digitHoldTime",
  // then nothing for "digitHoldTime".  If the digit is odd (1,3,5,7,9), then also
  // display the decimal point.

  for (int i = 0; i <= 9; i++)
  {
    SetLEDPortBits(PortDataPtr, DigitToSegSequence[i], 0);
    delay(digitHoldTime);
    SetLEDPortBits(PortDataPtr, 0b11111111, 1);
  }
}
