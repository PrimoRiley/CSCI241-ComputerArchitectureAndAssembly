; Description: ATMega2560 AVR assembly language "Lab1" program.

#define __SFR_OFFSET 0
#include "avr/io.h"   // AVR processor I/O definitions.

; Internal symbols referenced from external code.

.global Setup_Test_Lab1
.global Loop_Test_Lab1

; External symbols referenced from internal code.

; These are two special routines that preserve all 32 general purpose
; registers (r0 through r31), as well as the status register (SREG).

.global AVR_DisplayR18        // Display R18 contents in LED bank, then pause.
.global AVR_Display16BitR18   // Display 16-bit r19:r18 in LED bank, then pause.

; These routines adhere to the "AVR GNU Calling Conventions" and so
; must routines that call them.

.global AVR_SetupLedPort      // Initialize bank of 8 LEDs
.global AVR_SetupBuzzer       // Initialize buzzer
.global AVR_SetupButtonA      // Initialize pushbutton "A"

.global AVR_TurnLedsOn        // Turn LEDs on based on bits in r24
.global AVR_TurnLedsOff       // Turn LEDs off based on bits in r24
.global AVR_WaitMillis        // Wait milliseconds passed in r25:r24

; ---------------------------------------------------------------- -
; Setup code called once at start up.

Setup_Test_Lab1:
  call  AVR_SetupLedPort    ; Call utility routine to do the work
  call  AVR_SetupBuzzer     ; Call utility routine to do the work
  call  AVR_SetupButtonA    ; Call utility routine to do the work
  ret                       ; Return to our caller

; ---------------------------------------------------------------- -
; Main loop code called repeatedly.
;
; IMPORTANT:
;
; Unless indicated otherwise, all subroutines must adhere to the
; "AVR GNU Calling Convention".  Here are the specifics:
;
; 1, A subroutine which calls another is refered to as "the caller".
; 2. A subroutine that's called by another is refered to as "the callee".
; 3. R0 is a scratch register which need not be preserved by callers or callees.
; 4. R1 MUST contain zero when a callee is entered and when it returns.
; 5. R18-R27, R30, R31 are "callee used" (a.k.a. "call clobbered"). When a
;    "call" or "rcall" is made, the caller CANNOT assume the callee will
;    preserve these register contents.
; 6. R2-R17, R28, R29 are "callee saved".  A called subroutine MUST preserve
;    these register contents.

; PARAMETER PASSING:
;
; 1. As many parameters as possible are passed into subroutines in r24:r25,
;    r22:r23, r20:rl21, r18:r19.  Additional parameters are passed on the stack.
; 2. As many values are returned as possible in r24:r25, r22:r23, r20:rl21,
;    r18:r19.  Additional values are returned on the stack.

Loop_Test_Lab1:

;********************* Start of (Lab) Test Code ***********************

;*** Mentored Lab Rotate Left / Right Example***

  push  r2                ;Preserve register contents
  
  clr   r2                ;Clear register contents
  sec                     ;Set the carry flag on
left_loop:
  rol   r2                ;Rotate left (LSB < - carry, carry < - MSB)
  rcall FlashR2C          ;Flash register in LEDs, preserving carry flag
  brcc  left_loop         ;Branch if carry clear (0), keep shifting left
right_loop:
  ror   r2                ;Rotate right (carry -> MSB, LSB -> carry)
  rcall FlashR2C          ;Flash register in LEDs, preserving carry flag
  brcc  right_loop        ;Branch if carry clear (0), keep shifting right
  rjmp  left_loop         ;Jump back and change shift direction

  pop   r2                ;Restore register contents
  ret                     ;Return to our caller

;Subroutine which flashes the contents of r2 on, then off
;for "HoldTime" milliseconds.  Preserves state of carry flag.
;
; (This subroutine must follow the "AVR GNU Calling Convention".)

.equ  HoldTime, 20

FlashR2C:

  in    r24,SREG          ;Preserve carry flag state
  push  r24

  mov   r24,r2
  call  AVR_TurnLedsOn

  ldi r24,lo8(HoldTime)
  ldi r25,hi8(HoldTime)
  call AVR_WaitMillis
  
  mov r24, r2
  call AVR_TurnLedsOff

  ldi r24,lo8(HoldTime)
  ldi r25,hi8(HoldTime)
  ;call AVR_WaitMillis

  pop   r24               ;Restore carry flag state
  out   SREG,r24   
     
  ret                     ;Return to our caller

;********************** End of (Lab) Test Code ************************

  ret                     ; Return to our caller
