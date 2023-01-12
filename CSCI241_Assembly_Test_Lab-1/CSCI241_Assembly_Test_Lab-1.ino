// Author: Wayne Wall
// Description: ATMega2560 Assembly Language Test Bed

// Place your assembly language code in one or more *.S files in the same
// folder as this program.  For example, assume you have some assembly code
// you place in the file "Test1.S".  Here are some conventions:
//
// 1. It's assumed your assembly language code has a "Setup_Test1" subroutine
//    which performs any setup at the assembly language level.  This subroutine
//    is passed nothing and returns nothing.
//
// 2. It's assumed your assembly language code has a "Loop_Test1" subroutine
//    which contains the main code.  This routine is passed nothing and returns
//    nothing.  It's called repeatedly.

extern "C"
{
  // External assembly language subroutines called from C code.

  void Setup_Test_Lab1(); // Setup code for assembly language program "Test1".
  void Loop_Test_Lab1();  // Main loop code for program "Test1".

};

// Put your setup code here.  Runs once at power up or reset.

void setup()
{
  Setup_Test_Lab1();
}

// Put your main code here, which is run repeatedly.

void loop()
{
  Loop_Test_Lab1();
}
