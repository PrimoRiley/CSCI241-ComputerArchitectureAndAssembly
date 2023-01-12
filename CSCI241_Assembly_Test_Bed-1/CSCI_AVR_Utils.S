// Description: Atmel AVR processor assembly language utility routines.

#define __SFR_OFFSET 0
#include "avr/io.h"   // AVR processor I/O definitions.

;Internal symbols referenced from external code.

.global AVR_SetupLedPort
.global AVR_WaitMillis
.global AVR_TurnLedsOn
.global AVR_TurnLedsOff
.global AVR_SetupBuzzer
.global AVR_BeepBuzzer
.global AVR_BeepBuzzerOneSecond
.global AVR_SetupButtonA
.global AVR_WaitForButtonAClick
.global AVR_WaitForButtonAClick
.global AVR_DisplayR18

;External symbols referenced from within this module

.global delay

;-----------------------------------------------------------------
;Routine to display the byte in R18 in the 8 LEDs, beep the buzzer
;once, and wait for pushbutton "A" to be clicked before returning.
;
;Note: This routine can be called from anywhere and does NOT need
;      to be concerned about register usage, as ALL registers
;      are preseved.

AVR_DisplayR18:
  push  r0                ;Preserve ALL registers
  push  r1
  push  r2
  push  r3
  push  r4
  push  r5
  push  r6
  push  r7
  push  r8
  push  r9
  push  r10
  push  r11
  push  r12
  push  r13
  push  r14
  push  r15
  push  r16
  push  r17
  push  r18
  push  r19
  push  r20
  push  r21
  push  r22
  push  r23
  push  r24
  push  r25
  push  r26
  push  r27
  push  r28
  push  r29
  push  r30
  push  r31

  in    r0,SREG         ;Preserve status register contents
  push  r0

  push  r18                       ;Preserve r18 across subroutine call
  call  AVR_BeepBuzzerOneSecond   ;Alert user of diagnostic display
  pop   r18
  
  call  AVR_DisplayInLeds         ;Display r18 contents in LEDs.
  call  AVR_WaitForButtonAClick   ;Wait for button to be clicked

  pop   r0              ;Restore status register to previous contents
  out   SREG,r0                 

  pop   r31             ;Restore ALL registers
  pop   r30
  pop   r29
  pop   r28
  pop   r27
  pop   r26
  pop   r25
  pop   r24
  pop   r23
  pop   r22
  pop   r21
  pop   r20
  pop   r19
  pop   r18
  pop   r17
  pop   r16
  pop   r15
  pop   r14
  pop   r13
  pop   r12
  pop   r11
  pop   r10
  pop   r9
  pop   r8
  pop   r7
  pop   r6
  pop   r5
  pop   r4
  pop   r3
  pop   r2
  pop   r1
  pop   r0
  ret                     ;Return to our caller          

;-----------------------------------------------------------------
;DDRL/PORTL controls a group of GPIO pins connected to 8 LEDs.

AVR_SetupLedPort:
  ldi   r24,0xFF          ;All 8 GPIO pins are outputs
  sts   DDRL,r24
  ldi   r24,0xFF          ;Turns all LEDs (active low) off
  sts   PORTL,r24
  ret                     ;Return to our caller

 ;-----------------------------------------------------------------
 ;Routine to turn on LEDs. Pass bit mask in register R24.
 ;Bits of LEDs to turn on are set to 1.

 AVR_TurnLedsOn:
  lds   r25,PORTL         ;Get state of all LEDs
  com   r24               ;Form bit mask where bits to turn on are 0, others are 1.
  and   r25,r24           ;Set specified GPIO states LOW (which turns on LED)
  sts   PORTL,r25
  ret                     ;Return to our caller

 ;-----------------------------------------------------------------
 ;Routine to turn off LEDs. Pass bit mask in register R24.
 ;Bits of LEDs to turn off are set to 1.

 AVR_TurnLedsOff:
  lds   r25,PORTL         ;Get state of all LEDs
  or    r25,r24           ;Set specified GPIO states HIGH (which turns off LED)
  sts   PORTL,r25
  ret                     ;Return to our caller  

;-----------------------------------------------------------------
;Routine to display r18 contents in 8-bit LED display.

AVR_DisplayInLeds:
  push  r18               ;Preserve bit pattern to display
  mov   r24,r18           ;Prepare for call by copying pattern into r24
  rcall AVR_TurnLedsOn    ;Turn on LEDs corresponding to 1 bits.
  pop   r24               ;Restore bit pattern to display into r24
  com   r24               ;Turn off LEDs corresponding to 0 bits
  rcall AVR_TurnLedsOff   ; in the original pattern.
  ret                     ;Return to our caller

  ;-----------------------------------------------------------------
  ;Setup the active buzzer GPIO pin as an output.
  ;
  ;Note: Buzzer is connected to GPIO pin 51 (PORTB, bit 2)

  AVR_SetupBuzzer:
    sbi   DDRB,PINB2      ;Set buzzer GPIO as output
    cbi   PORTB,PINB2     ;Set buzzer GPIO LOW (silence)       
    ret                   ;Return to our caller

  ;-----------------------------------------------------------------
  ;Routine to "beep" active buzzer for 1 second

  AVR_BeepBuzzerOneSecond:
    ldi 24,lo8(1000)
    ldi 25,hi8(1000)
                          ;Fall into AVR_BeepBuzzer, which returns

  ;-----------------------------------------------------------------
  ;Routine to "beep" active buzzer for specified time.
  ;Time (in milliseconds) is passed in r25:r24
  ;
  ;Note: Buzzer is connected to GPIO pin 51 (PORTB, bit 2)

  AVR_BeepBuzzer:
    sbi   PORTB,PINB2     ;Set buzzer GPIO HIGH (makes sound)
    call  AVR_WaitMillis  ;Wait the specified period of time
    cbi   PORTB,PINB2     ;Set buzzer GPIO LOW (silence)
    ret                   ;Return to our caller

  ;-----------------------------------------------------------------
  ;Setup "Pushbutton A" pin as a GPIO input.
  ;
  ;Note: Button is connected to GPIO pin 52 (PORTB, bit 1)

  AVR_SetupButtonA:
    cbi   DDRB,PINB1      ;Set GPIO as input pin
    cbi   PORTB,PINB1     ;Enable internal pull-up resistor
    ret

 ;-----------------------------------------------------------------
 ;Wait for "Pushbutton A" to be pressed.
 ;
 ;Note: Button is connected to GPIO pin 52 (PORTB, bit 1)

 AVR_WaitForButtonAPress:
  sbic  PINB,PINB1                ;Skip if button GPIO is cleared (LOW)
  rjmp  AVR_WaitForButtonAPress   ;Button HIGH. Jump back and check again
  rcall AVR_WaitDebounceTime      ;Give time for switch debounce
  sbic  PINB,PINB1                ;Is button still LOW?
  rjmp  AVR_WaitForButtonAPress   ;No, Wait until it goes LOW again.
  ret                             ;Yes, return as button is pressed.

 ;-----------------------------------------------------------------
 ;Wait for "Pushbutton A" to be released.
 ;
 ;Note: Button is connected to GPIO pin 52 (PORTB, bit 1)

 AVR_WaitForButtonARelease:
  sbis  PINB,PINB1                ;Skip if button GPIO is set (HIGH)
  rjmp  AVR_WaitForButtonARelease ;Button LOW. Jump back and check again
  rcall AVR_WaitDebounceTime      ;Give time for switch debounce
  sbis  PINB,PINB1                ;Is button still HIGH?
  rjmp  AVR_WaitForButtonARelease ;No, Wait until it goes LOW again.
  ret                             ;Yes, return as button is released.

 ;-----------------------------------------------------------------
 ;Routine to wait for "Pushbutton A" to be pressed, then released.

 AVR_WaitForButtonAClick:
  rcall AVR_WaitForButtonAPress
  rcall AVR_WaitForButtonARelease
  ret                             ;Return to our caller
   
 ;-----------------------------------------------------------------
 ;Wait pushbutton debounce time.

 AVR_WaitDebounceTime:
  ldi r24,lo8(50)           ;Move debounce time (in millisecs) into r25:r24
  ldi r25,hi8(50)
                            ;Fall into AVR_WaitMillis, which will return
    
 ;-----------------------------------------------------------------
 ;Wait the number of milliseconds passed in r25:r24
 ;
 ;Currently, this is accomplished by passing a 32-bit value
 ;to the Arduino library "delay(...)" function.

AVR_WaitMillis:
  movw  r22,r24           ;Move 16-bit wait time into low order 32-bits
  clr   r24               ;Set high order 16-bits to zero
  clr   r25               
  call  delay             ;Call external library routine to do the work.
  ret                     ;Return to our caller
