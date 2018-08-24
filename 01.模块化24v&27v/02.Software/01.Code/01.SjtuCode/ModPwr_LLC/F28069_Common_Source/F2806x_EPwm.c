//###########################################################################
//
// FILE:   F2806x_EPwm.c
//
// TITLE:  F2806x EPwm Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V136 $
// $Release Date: Apr 15, 2013 $
//###########################################################################

#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File
#include "Global_declaration.h"

//---------------------------------------------------------------------------
// InitEPwm:
//---------------------------------------------------------------------------
// This function initializes the EPwm(s) to a known state.
//
void InitEPwm(void)
{

    //Initialize EPwm1
        EALLOW;

        EPwm1Regs.TBPRD = Period;                       // Set timer period
        EPwm1Regs.TBPHS.half.TBPHS = 0;                    // Phase is 0

        EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
        EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

        EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Count up down
        EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;          // Slave module
        EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
        EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;      // sync flow-through

        EPwm1Regs.TBCTR = 0x0000;                       // Clear counter

        // Setup shadow register load on ZERO
        EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
        EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
        EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

        // Set actions
        EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;              // Set PWM1A on event A, down count
        EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // Clear PWM1A on event A, up count
        EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;            // Clear PWM1B on event B, down count
        EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;              // Set PWM1B on event B, up count

        EPwm1Regs.CMPA.half.CMPA =0;
        EPwm1Regs.CMPB = 0;

        //deadband

        EPwm1Regs.DBCTL.bit.IN_MODE  = DBA_ALL; // EPWMxA In (from the action-qualifier) is the source for rising-edge delayed signal.
        EPwm1Regs.DBCTL.bit.POLSEL   = DB_ACTV_HIC;      // Active high (AH) mode. Neither EPWMxA nor EPWMxB is inverted (default).
        EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;      // Dead-band generation is bypassed for both output signals.

        EPwm1Regs.DBRED = 45;                         // 500ns,not active
        EPwm1Regs.DBFED = 45;                         // 500ns,not active

        //trip zone
        EPwm1Regs.TZCTL.bit.TZA = 2;
        EPwm1Regs.TZCTL.bit.TZB = 2;
//
//           //EPwm1Regs.ETSEL.bit.INTSEL = ET_CTRU_CMPA;
//           //EPwm1Regs.ETSEL.bit.INTEN = 0;
//           //EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;
//
//   // …Ë÷√EPWM¥•∑¢SOC
//           //EPwm1Regs.ETSEL.bit.SOCAEN = 1;
//           //EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;
//           EPwm1Regs.ETSEL.bit.SOCBEN = 1;
//           EPwm1Regs.ETSEL.bit.SOCBSEL = ET_CTR_ZERO;
//           //EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;
//           EPwm1Regs.ETPS.bit.SOCBPRD = ET_1ST;


           //Initialize EPwm2

           EALLOW;

           EPwm2Regs.TBPRD = Period - 1;                       // Set timer period
           EPwm2Regs.CMPA.half.CMPA = Period-200;                   // Set compare A value
           EPwm2Regs.CMPB = 0;
           EPwm2Regs.TBPHS.half.TBPHS = 0;                    // Phase is 0

           //TBCLK = SYSCLKOUT / (HSPCLKDIV °¡ CLKDIV)         // 90MHz
           EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
           EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

           EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Count up down
           EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
           EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
           EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through

           EPwm2Regs.TBCTR = 0x0000;                       // Clear counter

           // Setup shadow register load on ZERO
           EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
           EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
           EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
           EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;//CC_CTR_ZERO;//test by lishijun@20180820

           // Set actions
           EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;              // Set PWM1A on event A, down count
           EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // Clear PWM1A on event A, up count
           EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;            // Clear PWM1B on event B, down count
           EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;              // Set PWM1B on event B, up count

           EPwm2Regs.CMPA.half.CMPA = 0;
           EPwm2Regs.CMPB = 0;

           //deadband

           EPwm2Regs.DBCTL.bit.IN_MODE  = DBA_ALL; // EPWMxA In (from the action-qualifier) is the source for rising-edge delayed signal.
           EPwm2Regs.DBCTL.bit.POLSEL   = DB_ACTV_HIC;      // Active high (AH) mode. Neither EPWMxA nor EPWMxB is inverted (default).
           EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;      // Dead-band generation is bypassed for both output signals.

           EPwm2Regs.DBRED = 45;                         // 500ns,not active
           EPwm2Regs.DBFED = 45;                         // 500ns,not active

           //trip zone
           EPwm2Regs.TZCTL.bit.TZA = 2;
           EPwm2Regs.TZCTL.bit.TZB = 2;

//         EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
//         EPwm2Regs.ETSEL.bit.INTEN = 1;
//         EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;

           EDIS;



//   // Initialize EPwm3
//    EALLOW;
//
//    EPwm3Regs.TBPRD = Period - 1;                       // Set timer period
//    EPwm3Regs.CMPA.half.CMPA = 0;                   // Set compare A value
//    EPwm3Regs.CMPB = 0;
//    EPwm3Regs.TBPHS.half.TBPHS = 0;                    // Phase is 0
//
//    //TBCLK = SYSCLKOUT / (HSPCLKDIV °¡ CLKDIV)         // 90MHz
//    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
//    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//
//    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Count up down
//    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
//    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
//    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through
//
//    EPwm3Regs.TBCTR = 0x0000;                       // Clear counter
//
//    // Setup shadow register load on ZERO
//    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
//    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
//    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
//    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
//
//    // Set actions
//    EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;              // Set PWM1A on event A, down count
//    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // Clear PWM1A on event A, up count
//    EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;            // Clear PWM1B on event B, down count
//    EPwm3Regs.AQCTLB.bit.CBU = AQ_SET;              // Set PWM1B on event B, up count
//
//    EPwm3Regs.CMPA.half.CMPA = 0;
//    EPwm3Regs.CMPB = Period - 1;
//
//    //EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
//    //EPwm3Regs.ETSEL.bit.INTEN = 1;
//    //EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;
//    EPwm3Regs.ETSEL.bit.SOCAEN = 1;
//    EPwm3Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;
//    EPwm3Regs.ETSEL.bit.SOCBEN = 1;
//    EPwm3Regs.ETSEL.bit.SOCBSEL = ET_CTR_PRD;
//    EPwm3Regs.ETPS.bit.SOCAPRD = ET_1ST;
//    EPwm3Regs.ETPS.bit.SOCBPRD = ET_1ST;
//
////================================================
//// Configure digital compare event (DCAEVT2)
////================================================
//    EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT;   // DCAH = Comparator 1 output
//    EPwm3Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;        // DCAL = TZ2
//    EPwm3Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_COMP1OUT;   // DCBH = Comparator 1 output
//    EPwm3Regs.DCTRIPSEL.bit.DCBLCOMPSEL = DC_TZ2;        // DCBL = TZ2
//
//    EPwm3Regs.TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI; 		 // DCAEVT2 =  DCAH HIGH(will become active as Comparator output goes low)
//    EPwm3Regs.TZDCSEL.bit.DCBEVT1 = TZ_DCBH_HI; 		 // DCAEVT2 =  DCAH HIGH(will become active as Comparator output goes low)
//
//    EPwm3Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT2;           // DCAEVT2 = DCAEVT2 (not filtered)
//    EPwm3Regs.DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;  // Take async path
//
//    // Enable DCAEVT2 and DCBEVT2 are cycle-by-cycle trip sources
//    // Note:  DCxEVT1 events can be defined as one-shot.
//    //        DCxEVT2 events can be defined as cycle-by-cycle.
//
//    EPwm3Regs.TZSEL.bit.DCAEVT1 = 1;
//    EPwm3Regs.TZSEL.bit.DCBEVT1 = 1;
//
//    EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO;           // EPWMA force low
//    EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPWMB force low
//
//    EPwm3Regs.TZCTL.bit.DCAEVT1 = TZ_FORCE_LO;		  // EPWMA force low
//    EPwm3Regs.TZCTL.bit.DCBEVT1 = TZ_FORCE_LO;        // EPWMB force low
//	EPwm3Regs.TZCLR.all = 0xFFFF;
//
//	//EPwm3Regs.AQSFRC.bit.ACTSFA = 1;
//	//EPwm3Regs.AQSFRC.bit.ACTSFB = 1;


    EDIS;



}



//---------------------------------------------------------------------------
// Example: InitEPwmGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as EPwm pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitEPwmGpio(void)
{
   #if DSP28_EPWM1
       InitEPwm1Gpio();
   #endif // endif DSP28_EPWM1
   #if DSP28_EPWM2
       InitEPwm2Gpio();
   #endif // endif DSP28_EPWM2
   #if DSP28_EPWM3
       InitEPwm3Gpio();
   #endif // endif DSP28_EPWM3
   #if DSP28_EPWM4
       InitEPwm4Gpio();
   #endif // endif DSP28_EPWM4
   #if DSP28_EPWM5
       InitEPwm5Gpio();
   #endif // endif DSP28_EPWM5
   #if DSP28_EPWM6
       InitEPwm6Gpio();
   #endif // endif DSP28_EPWM6
   #if DSP28_EPWM7
       InitEPwm7Gpio();
   #endif // endif DSP28_EPWM7
   #if DSP28_EPWM8
       InitEPwm8Gpio();
   #endif // endif DSP28_EPWM8
}

#if DSP28_EPWM1
void InitEPwm1Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)

/* Configure EPWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}
#endif // endif DSP28_EPWM1

#if DSP28_EPWM2
void InitEPwm2Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)

/* Configure EPwm-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

    EDIS;
}
#endif // endif DSP28_EPWM2

#if DSP28_EPWM3
void InitEPwm3Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Disable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Disable pull-up on GPIO5 (EPWM3B)

/* Configure EPwm-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM3 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    EDIS;
}
#endif // endif DSP28_EPWM3

#if DSP28_EPWM4
void InitEPwm4Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;    // Disable pull-up on GPIO7 (EPWM4B)

/* Configure EPWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM4 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B

    EDIS;
}
#endif // endif DSP28_EPWM4

#if DSP28_EPWM5
void InitEPwm5Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;    // Disable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;    // Disable pull-up on GPIO9 (EPWM5B)

/* Configure EPWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B

    EDIS;
}
#endif // endif DSP28_EPWM5

#if DSP28_EPWM6
void InitEPwm6Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;    // Disable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;    // Disable pull-up on GPIO11 (EPWM6B)

/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B

    EDIS;
}
#endif // endif DSP28_EPWM6

#if DSP28_EPWM7
void InitEPwm7Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO30 = 1;	   // Disable pull-up on GPIO30 (EPWM7A)
    GpioCtrlRegs.GPBPUD.bit.GPIO40 = 1;    // Disable pull-up on GPIO40 (EPWM7A)
//  GpioCtrlRegs.GPBPUD.bit.GPIO58 = 1;	   // Disable pull-up on GPIO58 (EPWM7A)

    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;    // Disable pull-up on GPIO41 (EPWM7B)
//  GpioCtrlRegs.GPBPUD.bit.GPIO44 = 1;	   // Disable pull-up on GPIO44 (EPWM7B)

/* Configure EPWM-7 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM7 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 3;   // Configure GPIO30 as EPWM7A
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;   // Configure GPIO40 as EPWM7A
//  GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 3;   // Configure GPIO58 as EPWM7A

    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;   // Configure GPIO41 as EPWM7B
//  GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 3;   // Configure GPIO44 as EPWM7B

    EDIS;
}
#endif // endif DSP28_EPWM7

#if DSP28_EPWM8
void InitEPwm8Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;	   // Disable pull-up on GPIO30 (EPWM8A)
    GpioCtrlRegs.GPBPUD.bit.GPIO42 = 1;    // Disable pull-up on GPIO42 (EPWM8A)
    GpioCtrlRegs.GPBPUD.bit.GPIO43 = 1;    // Disable pull-up on GPIO43 (EPWM8B)

/* Configure EPWM-7 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM7 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 3;   // Configure GPIO30 as EPWM8A
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;   // Configure GPIO42 as EPWM8A
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 1;   // Configure GPIO43 as EPWM8B

    EDIS;
}
#endif // endif DSP28_EPWM8

//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as EPwm Synch pins
//

void InitEPwmSyncGpio(void)
{

//   EALLOW;

/* Configure EPWMSYNCI  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;     // Enable pull-up on GPIO6 (EPWMSYNCI)
   GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // Enable pull-up on GPIO32 (EPWMSYNCI)

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
   GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Configures GPIO6 for EPWMSYNCI operation
   GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Configures GPIO32 for EPWMSYNCI operation.

/* Configure EPWMSYNC0  */

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWMSYNCO)
   GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;   // Disable pull-up on GPIO33 (EPWMSYNCO)

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;   // Configures GPIO6 for EPWMSYNCO
   GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;  // Configures GPIO33 for EPWMSYNCO

}

//---------------------------------------------------------------------------
// Example: InitTzGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitTzGpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
// GpioCtrlRegs.GPBPUD.bit.GPIO42 = 0;	  // Enable pull-up on GPIO42 (TZ1)
// GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;	  // Enable pull-up on GPIO50 (TZ1)
   GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up on GPIO13 (TZ2)
// GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ2)
// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ2)
// GpioCtrlRegs.GPBPUD.bit.GPIO43 = 0;	  // Enable pull-up on GPIO43 (TZ2)
// GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;    // Enable pull-up on GPIO51 (TZ2)
   GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up on GPIO14 (TZ3)
// GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ3)
// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ3)
// GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;    // Enable pull-up on GPIO52 (TZ3)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO42 = 3;  // Asynch input GPIO42 (TZ1)
// GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = 3;  // Asynch input GPIO50 (TZ1)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;  // Asynch input GPIO13 (TZ2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ2)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO43 = 3;  // Asynch input GPIO43 (TZ2)
// GpioCtrlRegs.GPBQAEL2.bit.GPIO51 = 3;  // Asynch input GPIO51 (TZ2)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;  // Asynch input GPIO14 (TZ3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ3)
// GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 3;  // Asynch input GPIO52 (TZ3)


/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
// GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 2;  // Configure GPIO42 as TZ1
// GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 3;  // Configure GPIO50 as TZ1
   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as TZ2
// GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ2
// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ2
// GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 2;  // Configure GPIO43 as TZ2
// GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 3;  // Configure GPIO51 as TZ2
   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as TZ3
// GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ3
// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ3
// GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 3;  // Configure GPIO52 as TZ3

   EDIS;

}

//===========================================================================
// End of file.
//===========================================================================
