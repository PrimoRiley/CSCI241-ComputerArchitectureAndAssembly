; Description: Assembly language code.

#define __SFR_OFFSET 0
#include "avr/io.h"   // AVR processor I/O definitions.

; Internal symbols referenced from external code.

.global Setup_Assembly
.global SampleButtonTransitions

; External symbols referenced from internal code.

;These are two special routines that preserve all 32 general purpose
;registers (r0 through r31), as well as the status register (SREG).

.global AVR_DisplayR18        // Display R18 contents in LED bank, then pause.
.global AVR_Display16BitR18   // Display 16-bit r19:r18 in LED bank, then pause.

;These routines adhere to the "AVR GNU Calling Conventions" and so
;must routines that call them.

.global AVR_SetupLedPort      // Initialize bank of 8 LEDs
.global AVR_SetupBuzzer       // Initialize buzzer
.global AVR_SetupButtonA      // Initialize pushbutton "A"
.global AVR_SetupButtonB      // Initialize pushbutton "B"

.global AVR_WaitMillis        // Wait milliseconds passed in r25:r24

; ---------------------------------------------------------------- -
; Setup code called once at start up.

Setup_Assembly:
  call  AVR_SetupLedPort    ;Call utility routine to do the work
  call  AVR_SetupBuzzer     ;Call utility routine to do the work
  call  AVR_SetupButtonA    ;Call utility routine to do the work
  call  AVR_SetupButtonB    ;Call utility routine to do the work
  ret                       ;Return to our caller

; ---------------------------------------------------------------- -
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

;Notes:
;
; o The first parameter (passed in r25:r24) is the base address of an
;   array of unsigned integers (uint16_t) where the time (in milliseconds)
;   between transitions is to be stored.
;
; o The second parameter (passed in r23:r22) is an unsigned integer
;   (uint16_t) which is the maximum number of elements available in the
;   transition time array.
;
; o Use the Y register pair (r29:r28, a.k.a., YH:YL) to index/subscript
;   off the array base address to store each array element.
;
; o This subroutine's task is to wait until GPIO pin 53 (PORTB, bit 0,
;   a.k.a., Pushbutton "B") goes LOW (i.e., button pressed), then count the
;   number of millisecond time intervals until the button state transitions
;   to HIGH, store that value into the first array element, then count the
;   number of millisecond time intervals until the button transitions back
;   to LOW, store that value into the next array element and so on, until
;   either GPIO pin 52 (PORTB, bit 1, a.k.a., Pushbutton "A") goes LOW or
;   the maximum number of transition counts have been stored into the array.
;   The subroutine returns the number of counts actually stored in the array.

SampleButtonTransitions:

  ;Macro to do a 16-bit increment on any register pair

  .macro inc_pair reg_low, reg_high

    inc   \reg_low
    brne   .+2
    inc   \reg_high
  
  .endm

  ;Define meaningful names for register pair to hold number of array
  ;elements actually stored.

  #define numele_low r16
  #define numele_high r17

  ;Define meaningful names for register pair to hold max elements available.

  #define maxele_low r14
  #define maxele_high r15

  ;Define meaningful names for register pair to hold millisecond counts

  #define mcount_low r12
  #define mcount_high r13

  ;Define meaningful name for register to hold last Pushbutton "B" state

  #define PBB_LastState r11
 
  push  YL                ;Preserve registers we will use,
  push  YH                ; but callees will preserve.
  push  numele_low
  push  numele_high
  push  maxele_low
  push  maxele_high
  push  mcount_low
  push  mcount_high

  ;***** Replace this temporary code with your Homework #6 code *****

  clr   numele_low        ;Indicate there are no transition times stored (yet)
  clr   numele_high

  ;Note: Button "A" is connected to GPIO pin 52 (PORTB, bit 1)
  ;Note: Button "B"vis connected to GPIO pin 53 (PORTB, bit 0)

  movw  Y,r24                       ;Move 16-bit array base address into Y register pair
  movw  maxele_low,r22              ;Move 16-bit max array element value into register pair

check_buttons:

  sbis  PINB,PINB1                  ;Skip if button "A" not pressed (i.e., HIGH)
  rjmp  All_Done                    ;Button pressed.  We're all done.
  sbic  PINB,PINB0                  ;Skip if button "B" is pressed (i.e., LOW)
  rjmp  check_buttons               ;Button not pressed. Loop back and wait.

  ;Here when button "B" is pressed

  ldi   r24,0x01                    ;Turn on LSB LED
  call  AVR_TurnLedsOn  

  clr   mcount_low                  ;Reset millisecond timer
  clr   mcount_high

buttonB_pressed:
  ldi   r24,1                       ;Load a value of 1 into register pair
  clr   r25
  call  AVR_WaitMillis              ;Wait for 1 millisecond
  inc_pair  mcount_low, mcount_high ;Count this millisecond interval
  sbis  PINB,PINB1                  ;Skip if button "A" not pressed (i.e., HIGH)
  rjmp  All_Done                    ;Button pressed.  We're all done.
  sbis  PINB,PINB0                  ;Skip if button "B" released (i.e., HIGH)
  rjmp  buttonB_pressed             ;Button still pressed.  Loop back and wait.

  ldi   r24,0x01                    ;Turn off LSB LED
  call  AVR_TurnLedsOff
  
  st    Y+,mcount_low               ;Store millisecond count into caller's array
  st    Y+,mcount_high
  inc_pair numele_low, numele_high  ;Increment number of times returned

  clr mcount_low
  clr mcount_high
  
  cp    maxele_low,numele_low       ;Have we filled the caller's array yet?
  brne  buttonB_released            ;Branch if not. Wait for next button press
  cp    maxele_high,numele_high     ;Maybe, compare high order bytes.
  brne  buttonB_released            ;Branch if not. Wait for next button press

buttonB_released:
  ldi r24,1                         ;Load a value of 1 into register pair
  clr r25
  call AVR_WaitMillis
  inc_pair  mcount_low, mcount_high ;Counts milliseconds 
  sbis  PINB,PINB1                  ;Skip if button "A" not pressed (i.e., HIGH)
  rjmp  All_Done                    ;Button pressed.  We're all done.
  sbic PINB,PINB0                   ;skips if button "B" is pressed (LOW)
  rjmp buttonB_released             ;button still released so loop back
  
  st    Y+,mcount_low     ;Store millisecond count into caller's array
  st    Y+,mcount_high
  
  inc_pair numele_low, numele_high  ;Increment number of times returned
  
  cp    maxele_low,numele_low       ;Have we filled the caller's array yet?
  brne  check_buttons               ;Branch if not. Wait for next button press
  cp    maxele_high,numele_high     ;Maybe, compare high order bytes.
  brne  check_buttons               ;Branch if not. Wait for next button press  

All_Done:

  ;***** End of temporary code *****

  mov   r24,numele_low    ;Return number of elements stored in caller's array
  mov   r25,numele_high
  
  pop   mcount_high       ;Restore saved register values
  pop   mcount_low
  pop   maxele_high
  pop   maxele_low
  pop   numele_high
  pop   numele_low
  pop   YH
  pop   YL
  ret                     ;Return to our caller
 
