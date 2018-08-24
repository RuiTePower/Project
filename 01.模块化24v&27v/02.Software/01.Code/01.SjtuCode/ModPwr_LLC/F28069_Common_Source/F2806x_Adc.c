//###########################################################################
//
// FILE:    F2806x_Adc.c
//
// TITLE:   F2806x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V136 $
// $Release Date: Apr 15, 2013 $
//###########################################################################

#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File

#define ADC_usDELAY  1000L

//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
// NOTE: ADC INIT IS DIFFERENT ON F2806x DEVICES COMPARED TO OTHER 28X DEVICES
//
//  *IMPORTANT*
//  IF RUNNING FROM FLASH, PLEASE COPY OVER THE SECTION "ramfuncs"  FROM FLASH
//  TO RAM PRIOR TO CALLING InitSysCtrl(). THIS PREVENTS THE MCU FROM THROWING 
//  AN EXCEPTION WHEN A CALL TO DELAY_US() IS MADE. 
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);

    // *IMPORTANT*
    // The Device_cal function, which copies the ADC calibration values from TI reserved
    // OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
    // Boot ROM. If the boot ROM code is bypassed during the debug process, the
    // following function MUST be called for the ADC to function according
    // to specification. The clocks to the ADC MUST be enabled before calling this
    // function.
    // See the device data manual and/or the ADC Reference
    // Manual for more information.

        EALLOW;
        SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
        (*Device_cal)();
        EDIS;

    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
    // after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
    // CPU_RATE define statement in the F2806x_Examples.h file must
    // contain the correct CPU clock period in nanoseconds.
    EALLOW;
    AdcRegs.ADCCTL1.bit.ADCBGPWD  = 1;      // Power ADC BG
    AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;      // Power reference
    AdcRegs.ADCCTL1.bit.ADCPWDN   = 1;      // Power ADC
    AdcRegs.ADCCTL1.bit.ADCENABLE = 1;      // Enable ADC
    AdcRegs.ADCCTL1.bit.ADCREFSEL = 1;      // Select exteral BG
    EDIS;

    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

    EALLOW;
    AdcRegs.ADCCTL2.bit.CLKDIV2EN = 1;
    EDIS;

    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels


    //setup adc channal
    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 0;  //Enable overlap mode
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;    //ADCINT1 trips after AdcResults latch


    //AdcRegs.ADCSOC0CTL.all=0x0006;          // 这条指令与下面3条指令等价
    AdcRegs.ADCSOC0CTL.bit.CHSEL  = 2;        // 设置 SOC0 选择 ADCINA2
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0;       // 触发源为Soft trigsel
    AdcRegs.ADCSOC0CTL.bit.ACQPS  = 6;        // 设置SOC0的采样/保持窗为7个ADC时钟周期 (7 = ACQPS + 1)


    AdcRegs.ADCSOC1CTL.bit.CHSEL  = 3;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC1CTL.bit.ACQPS  = 6;          // SOC1 选择 ADCINA3，触发源为Soft trigsel，ACQPS = 6


    AdcRegs.ADCSOC2CTL.bit.CHSEL  = 4;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC2CTL.bit.ACQPS  = 6;         // SOC2 选择 ADCINA4，触发源为Soft trigsel，ACQPS = 6


    AdcRegs.ADCSOC3CTL.bit.CHSEL  = 5;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC3CTL.bit.ACQPS  = 6;          // SOC3 选择 ADCINA5，触发源为Soft trigsel，ACQPS = 6


    AdcRegs.ADCSOC4CTL.bit.CHSEL  = 6;
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC4CTL.bit.ACQPS  = 6;          // SOC4 选择 ADCINA6，触发源为Soft trigsel，ACQPS = 6

    AdcRegs.ADCSOC5CTL.bit.CHSEL  = 7;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC5CTL.bit.ACQPS  = 6;          // SOC5 选择 ADCINA7，触发源为Soft trigsel，ACQPS = 6

    AdcRegs.ADCSOC6CTL.bit.CHSEL  = 8;
    AdcRegs.ADCSOC6CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC6CTL.bit.ACQPS  = 6;          // SOC6 选择 ADCINB0，触发源为Soft trigsel，ACQPS = 6

    AdcRegs.ADCSOC7CTL.bit.CHSEL  = 9;
    AdcRegs.ADCSOC7CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC7CTL.bit.ACQPS  = 6;         // SOC7 选择 ADCINB1，触发源为Soft trigsel，ACQPS = 6

    AdcRegs.ADCSOC8CTL.bit.CHSEL  = 10;
    AdcRegs.ADCSOC8CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC8CTL.bit.ACQPS  = 6;          // SOC8 选择 ADCINB2，触发源为Soft trigsel，ACQPS = 6

    AdcRegs.ADCSOC9CTL.bit.CHSEL  = 11;
    AdcRegs.ADCSOC9CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC9CTL.bit.ACQPS  = 6;          // SOC9 选择 ADCINB3，触发源为Soft trigsel，ACQPS = 6

    AdcRegs.ADCSOC10CTL.bit.CHSEL  = 12;
    AdcRegs.ADCSOC10CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC10CTL.bit.ACQPS  = 6;          // SOC10 选择 ADCINB4，触发源为Soft trigsel，ACQPS = 6

    AdcRegs.ADCSOC11CTL.bit.CHSEL  = 13;
    AdcRegs.ADCSOC11CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC11CTL.bit.ACQPS  = 6;          // SOC11 选择 ADCINB5，触发源为Soft trigsel，ACQPS = 6


    AdcRegs.INTSEL1N2.bit.INT1SEL   = 1;    //setup EOC1 to trigger ADCINT1 to fire
    AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;    //Disable ADCINT1 Continuous mode
    AdcRegs.INTSEL1N2.bit.INT1E     = 1;    //Enabled ADCINT1
    EDIS;

    EALLOW;

//// COMP1
//    //AdcRegs.ADCCTL1.bit.ADCBGPWD = 1;        //Comparator shares the internal BG reference of the ADC, must be powered even if ADC is unused
//    Comp1Regs.COMPCTL.bit.COMPDACEN = 1;     //Power up Comparator 1 locally
//    // Comp1Regs.COMPCTL.bit.COMPSOURCE = 1;    //Connect the inverting input to pin COMP1B
//    											//Uncomment previous line to use COMP1B
//    											//instead of internal DAC
//    Comp1Regs.COMPCTL.bit.COMPSOURCE = 0;    //Connect the inverting input to the internal DAC
//    Comp1Regs.DACVAL.bit.DACVAL =961;	//Set DAC output to midpoint
//
//// COMP2
//
//    Comp2Regs.COMPCTL.bit.COMPDACEN = 1;     //Power up Comparator 1 locally
//    // Comp1Regs.COMPCTL.bit.COMPSOURCE = 1;    //Connect the inverting input to pin COMP1B
//    											//Uncomment previous line to use COMP1B
//    											//instead of internal DAC
//    Comp2Regs.COMPCTL.bit.COMPSOURCE = 0;    //Connect the inverting input to the internal DAC
//    Comp2Regs.DACVAL.bit.DACVAL =961;	//Set DAC output to midpoint

    EDIS;
}

void InitAdcAio()
{

   EALLOW;

/* Configure ADC pins using AIO regs*/
// This specifies which of the possible AIO pins will be Analog input pins.
// NOTE: AIO1,3,5,7-9,11,13,15 are analog inputs in all AIOMUX1 configurations.
// Comment out other unwanted lines.

    GpioCtrlRegs.AIOMUX1.bit.AIO2 = 2;    // Configure AIO2 for A2 (analog input) operation
    GpioCtrlRegs.AIOMUX1.bit.AIO4 = 2;    // Configure AIO4 for A4 (analog input) operation
    GpioCtrlRegs.AIOMUX1.bit.AIO6 = 2;    // Configure AIO6 for A6 (analog input) operation
    GpioCtrlRegs.AIOMUX1.bit.AIO10 = 2;   // Configure AIO10 for B2 (analog input) operation
    GpioCtrlRegs.AIOMUX1.bit.AIO12 = 2;   // Configure AIO12 for B4 (analog input) operation
    GpioCtrlRegs.AIOMUX1.bit.AIO14 = 2;   // Configure AIO14 for B6 (analog input) operation

    EDIS;
}


/* AdcoffsetSelfCal-
   This function re-calibrates the ADC zero offset error by converting the VREFLO reference with
   the ADC and modifying the ADCOFFTRIM register. VREFLO is sampled by the ADC using an internal
   MUX select which connects VREFLO to A5 without sacrificing an external ADC pin. This
   function calls two other functions:
   - AdcChanSelect(channel) 锟絪elects the ADC channel to convert
   - AdcConversion() 锟絠nitiates several ADC conversions and returns the average
*/
void AdcOffsetSelfCal()
{
    Uint16 AdcConvMean;
    EALLOW;
    AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;                  //Select internal reference mode
    AdcRegs.ADCCTL1.bit.VREFLOCONV = 1;                 //Select VREFLO internal connection on B5
    AdcChanSelect(13);                                  //Select channel B5 for all SOC
    AdcRegs.ADCOFFTRIM.bit.OFFTRIM = 80;                //Apply artificial offset (+80) to account for a negative offset that may reside in the ADC core
    AdcConvMean = AdcConversion();                      //Capture ADC conversion on VREFLO
    AdcRegs.ADCOFFTRIM.bit.OFFTRIM = 80 - AdcConvMean;  //Set offtrim register with new value (i.e remove artical offset (+80) and create a two's compliment of the offset error)
    AdcRegs.ADCCTL1.bit.VREFLOCONV = 0;                 //Select external ADCIN5 input pin on B5
    EDIS;
}

/*  AdcChanSelect-
    This function selects the ADC channel to convert by setting all SOC channel selects to a single channel.

     * IMPORTANT * This function will overwrite previous SOC channel select settings. Recommend saving
           the previous settings.
 */
void AdcChanSelect(Uint16 ch_no)
{
    AdcRegs.ADCSOC0CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC1CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC2CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC3CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC4CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC5CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC6CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC7CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC8CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC9CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC10CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC11CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC12CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC13CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC14CTL.bit.CHSEL= ch_no;
    AdcRegs.ADCSOC15CTL.bit.CHSEL= ch_no;
} //end AdcChanSelect

/* AdcConversion -
   This function initiates several ADC conversions and returns the average. It uses ADCINT1 and ADCINT2
   to "ping-pong" between SOC0-7 and SOC8-15 and is referred to as "ping-pong" sampling.

     * IMPORTANT * This function will overwrite previous ADC settings. Recommend saving previous settings.
*/
Uint16 AdcConversion(void)
{
    Uint16 index, SampleSize, Mean, ACQPS_Value;
    Uint32 Sum;

    index       = 0;            //initialize index to 0
    SampleSize  = 256;          //set sample size to 256 (**NOTE: Sample size must be multiples of 2^x where is an integer >= 4)
    Sum         = 0;            //set sum to 0
    Mean        = 999;          //initialize mean to known value

    //Set the ADC sample window to the desired value (Sample window = ACQPS + 1)
    ACQPS_Value = 6;
    AdcRegs.ADCSOC0CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC1CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC2CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC3CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC4CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC5CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC6CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC7CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC8CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC9CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC10CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC11CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC12CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC13CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC14CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC15CTL.bit.ACQPS = ACQPS_Value;


    //Enable ping-pong sampling

    // Enabled ADCINT1 and ADCINT2
    AdcRegs.INTSEL1N2.bit.INT1E = 1;
    AdcRegs.INTSEL1N2.bit.INT2E = 1;

    // Disable continuous sampling for ADCINT1 and ADCINT2
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0;
    AdcRegs.INTSEL1N2.bit.INT2CONT = 0;

    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;    //ADCINTs trigger at end of conversion

    // Setup ADCINT1 and ADCINT2 trigger source
    AdcRegs.INTSEL1N2.bit.INT1SEL = 6;      //EOC6 triggers ADCINT1
    AdcRegs.INTSEL1N2.bit.INT2SEL = 14;     //EOC14 triggers ADCINT2

    // Setup each SOC's ADCINT trigger source
    AdcRegs.ADCINTSOCSEL1.bit.SOC0  = 2;    //ADCINT2 starts SOC0-7
    AdcRegs.ADCINTSOCSEL1.bit.SOC1  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC2  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC3  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC4  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC5  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC6  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC7  = 2;
    AdcRegs.ADCINTSOCSEL2.bit.SOC8  = 1;    //ADCINT1 starts SOC8-15
    AdcRegs.ADCINTSOCSEL2.bit.SOC9  = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC10 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC11 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC12 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC13 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC14 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC15 = 1;

    DELAY_US(ADC_usDELAY);                  // Delay before converting ADC channels


    //ADC Conversion

    AdcRegs.ADCSOCFRC1.all = 0x00FF;  // Force Start SOC0-7 to begin ping-pong sampling

    while( index < SampleSize ){

        //Wait for ADCINT1 to trigger, then add ADCRESULT0-7 registers to sum
        while (AdcRegs.ADCINTFLG.bit.ADCINT1 == 0){}
        AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;   //Must clear ADCINT1 flag since INT1CONT = 0
        Sum += AdcResult.ADCRESULT0;
        Sum += AdcResult.ADCRESULT1;
        Sum += AdcResult.ADCRESULT2;
        Sum += AdcResult.ADCRESULT3;
        Sum += AdcResult.ADCRESULT4;
        Sum += AdcResult.ADCRESULT5;
        Sum += AdcResult.ADCRESULT6;
        Sum += AdcResult.ADCRESULT7;

        //Wait for ADCINT2 to trigger, then add ADCRESULT8-15 registers to sum
        while (AdcRegs.ADCINTFLG.bit.ADCINT2 == 0){}
        AdcRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;   //Must clear ADCINT2 flag since INT2CONT = 0
        Sum += AdcResult.ADCRESULT8;
        Sum += AdcResult.ADCRESULT9;
        Sum += AdcResult.ADCRESULT10;
        Sum += AdcResult.ADCRESULT11;
        Sum += AdcResult.ADCRESULT12;
        Sum += AdcResult.ADCRESULT13;
        Sum += AdcResult.ADCRESULT14;
        Sum += AdcResult.ADCRESULT15;

        index+=16;

    } // end data collection

    //Disable ADCINT1 and ADCINT2 to STOP the ping-pong sampling
    AdcRegs.INTSEL1N2.bit.INT1E = 0;
    AdcRegs.INTSEL1N2.bit.INT2E = 0;

    Mean = Sum / SampleSize;    //Calculate average ADC sample value

    return Mean;                //return the average

}//end AdcConversion

//===========================================================================
// End of file.
//===========================================================================
