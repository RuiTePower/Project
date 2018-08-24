//###########################################################################
//
// FILE:	F2806x_Gpio.c
//
// TITLE:	F2806x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V136 $
// $Release Date: Apr 15, 2013 $
//###########################################################################

#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File

//---------------------------------------------------------------------------
// InitGpio:
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example.
void InitGpio(void)
{
   EALLOW;

   // Each GPIO pin can be:
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs
   GpioCtrlRegs.GPAMUX1.all = 0x0000;     // GPIO functionality GPIO0-GPIO15
   GpioCtrlRegs.GPAMUX2.all = 0x0000;     // GPIO functionality GPIO16-GPIO31
   GpioCtrlRegs.GPBMUX1.all = 0x0000;     // GPIO functionality GPIO32-GPIO47
   GpioCtrlRegs.GPBMUX2.all = 0x0000;	  // GPIO functionality GPIO48-GPIO63
   GpioCtrlRegs.AIOMUX1.all = 0x0000;     // Dig.IO funct. applies to AIO2,4,6,10,12,14

   GpioCtrlRegs.GPADIR.all = 0x0000;      // GPIO0-GPIO31 are GP inputs
   GpioCtrlRegs.GPBDIR.all = 0x0000;      // GPIO32-GPIO63 are inputs
   GpioCtrlRegs.AIODIR.all = 0x0000;      // AIO2,4,6,10,12,14 are digital inputs

   // Each input can have different qualification
   // a) input synchronized to SYSCLKOUT
   // b) input qualified by a sampling window
   // c) input sent asynchronously (valid for peripheral inputs only)
   GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT
   GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
   GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO47 Synch to SYSCLKOUT
   GpioCtrlRegs.GPBQSEL2.all = 0x0000;	  // GPIO48-GPIO63 Synch to SYSCLKOUT

   // Pull-ups can be enabled or disabled.
   //GpioCtrlRegs.GPAPUD.all = 0x0000;      // Pullup's enabled GPIO0-GPIO31
   //GpioCtrlRegs.GPBPUD.all = 0x0000;      // Pullup's enabled GPIO32-GPIO44
   GpioCtrlRegs.GPAPUD.all = 0xFFFF;    // Pullup's disabled GPIO0-GPIO31
   GpioCtrlRegs.GPBPUD.all = 0xFFFF;    // Pullup's disabled GPIO32-GPIO44


/*********************************************************************/
/*************************** GPIO  input *****************************/
/*********************************************************************/

   //DIP Switch Addr1 input
   GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0; // GPIO39 = GPIO39
   GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;  // GPIO39 = input
   //DIP Switch Addr2 input
   GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0; // GPIO53 = GPIO53
   GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;  // GPIO53 = input


///*********************************************************************/
///*************************** SCI A and B *****************************/
///*********************************************************************/
   // Enable SCI-A on GPIO28 - GPIO12
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;	   // Enable pull-up for GPIO12 (SCITXDA)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)

	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;   // Configure GPIO12 for SCITXDA operation

   // Enable SCI-B on GPIO44 - GPIO9
	GpioCtrlRegs.GPBPUD.bit.GPIO44 = 0;    // Enable pull-up for GPIO44 (SCIRXDB)
	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;	   // Enable pull-up for GPIO9 (SCITXDB)
	GpioCtrlRegs.GPBQSEL1.bit.GPIO44 = 3;  // Asynch input GPIO44 (SCIRXDB)

    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 2;   // Configure GPIO44 for SCIRXDB operation
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;   // Configure GPIO9 for SCITXDB operation


///*********************************************************************/
///*************************** GPIO  output ****************************/
///*********************************************************************/
     // Enable an GPIO output

	 // DIO1 Signal
	 GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // Enable pullup on GPIO5
	 GpioDataRegs.GPASET.bit.GPIO5 = 1;   // Load output latch
	 GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;  // GPIO5 = GPIO5
	 GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;   // GPIO5 = output

	 // DIO2 Signal
	 GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // Enable pullup on GPIO4
	 GpioDataRegs.GPASET.bit.GPIO4 = 1;   // Load output latch
	 GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;  // GPIO4 = GPIO4
	 GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;   // GPIO4 = output

	 // DIO3 Signal
	 GpioCtrlRegs.GPAPUD.bit.GPIO23 = 1;   // Disable pullup on GPIO23
	 GpioDataRegs.GPASET.bit.GPIO23 = 1;   // Load output latch
	 GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;  // GPIO23 = GPIO23
	 GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;   // GPIO23 = output

	 // DIO4 Signal
	 GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pullup on GPIO33
	 GpioDataRegs.GPBSET.bit.GPIO33 = 1;   // Load output latch
	 GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;  // GPIO33 = GPIO33
	 GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;   // GPIO33 = output


     // LED1 Signal
     GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pullup on GPIO24
     GpioDataRegs.GPASET.bit.GPIO24 = 1;   // Load output latch
     GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;  // GPIO24 = GPIO24
     GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;   // GPIO24 = output

     // LED2 Signal
     GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;   // Enable pullup on GPIO14
     GpioDataRegs.GPASET.bit.GPIO14 = 1;   // Load output latch
     GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;  // GPIO14 = GPIO14
     GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;   // GPIO14 = output

     // LED3 Signal
     GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pullup on GPIO13
     GpioDataRegs.GPASET.bit.GPIO13 = 1;   // Load output latch
     GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;  // GPIO13 = GPIO13
     GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;   // GPIO13 = output

     // LED4 Signal
     GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;   // Enable pullup on GPIO58
     GpioDataRegs.GPBSET.bit.GPIO58 = 1;   // Load output latch
     GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;  // GPIO58 = GPIO58
     GpioCtrlRegs.GPBDIR.bit.GPIO58 = 1;   // GPIO58 = output


//   // Passive contact NO.4 output
//   GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // Enable pullup on GPIO2
//   GpioDataRegs.GPASET.bit.GPIO2 = 1;   // Load output latch
//   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;  // GPIO2 = GPIO2
//   GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;   // GPIO2 = output
//
//   // Communication LED Signal
//   GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pullup on GPIO24
//   GpioDataRegs.GPASET.bit.GPIO24 = 1;   // Load output latch
//   GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;  // GPIO24 = GPIO24
//   GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;   // GPIO24 = output
//
//   // Passive contact NO.2 output
//   GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;   // Enable pullup on GPIO26
//   GpioDataRegs.GPASET.bit.GPIO26 = 1;   // Load output latch
//   GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;  // GPIO26 = GPIO26
//   GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;   // GPIO26 = output
//
//   // Passive contact NO.1 output
//   GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   // Enable pullup on GPIO27
//   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // Load output latch
//   GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;  // GPIO27 = GPIO27
//   GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;   // GPIO27 = output
//
//   // Passive contact NO.3 output
//   GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // Enable pullup on GPIO3
//   GpioDataRegs.GPASET.bit.GPIO3 = 1;   // Load output latch
//   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;  // GPIO3 = GPIO3
//   GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;   // GPIO3 = output
//
//   // AUX Relay signal
//   GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // Enable pullup on GPIO8
//   GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;   // Load output latch
//   GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;  // GPIO8 = GPIO8
//   GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;   // GPIO8 = output
//
//   // 485 COMMUNICATION IO1
//   GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // Enable pullup on GPIO9
//   GpioDataRegs.GPASET.bit.GPIO9 = 1;   // Load output latch
//   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;  // GPIO9 = GPIO9
//   GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;   // GPIO9 = output

/*********************************************************************/
/******************************* EPWM ********************************/
/*********************************************************************/

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B


    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B


    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;    // Disable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;    // Disable pull-up on GPIO11 (EPWM6B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B


    GpioCtrlRegs.GPBPUD.bit.GPIO40 = 1;    // Disable pull-up on GPIO40 (EPWM7A)
    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;    // Disable pull-up on GPIO41 (EPWM7B)
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;   // Configure GPIO40 as EPWM7A
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;   // Configure GPIO41 as EPWM7B


   EDIS;

}



//===========================================================================
// End of file.
//===========================================================================
