;Description: ATMega2560 AVR assembly languate "Test1" program.

#define __SFR_OFFSET 0
#include "avr/io.h"   // AVR processor I/O definitions.

;Internal symbols referenced from external code.

.global Setup_Test1
.global Loop_Test1

;External symbols referenced from internal code.

.global AVR_SetupLedPort
.global AVR_SetupBuzzer
.global AVR_SetupButtonA
.global AVR_DisplayR18

;-----------------------------------------------------------------
; Setup code called once at start up.

Setup_Test1:
  call  AVR_SetupLedPort    ;Call utility routine to do the work
  call  AVR_SetupBuzzer     ;Call utility routine to do the work
  call  AVR_SetupButtonA    ;Call utility routine to do the work
  ret                       ;Return to our caller

;-----------------------------------------------------------------
; Main loop code called repeatedly.
;
; IMPORTANT:
;
; This is an extremely simple test bed!  The only external
; subroutine you should call is AVR_DisplayR18, which beeps the
; buzzer, displays the byte in r18 in the 8 utility breadboard LEDs,
; and waits for you to click (i.e., press and release)
; Pushbutton "A".
;
; IMPORTANT: You are limited to modifying r0, r18 through 27, r30, r31.
;            Do NOT modify registers r1 through r17 or r28, r29!

Loop_Test1:

;********************* Start of Test Code ***********************

  ldi   r18,5  ;Load bit pattern into register
  call  AVR_DisplayR18    ;Display value
  ;inc_loop:
  neg r18
  ;com   r18               ;Flip all bits
  call  AVR_DisplayR18    ;Display value
  add r18,r19
  call AVR_DisplayR18
  ;jmp inc_loop

;********************** End of Test Code ************************

  ret                     ;Return to our caller
