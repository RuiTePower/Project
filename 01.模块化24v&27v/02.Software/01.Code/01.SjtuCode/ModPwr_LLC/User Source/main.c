/*
 * main.c
 *
 *  Created on: 2018Äê1ÔÂ19ÈÕ
 *      Author: comeonbaby1
 */

#include "DSP28x_Project.h"
#include "Global_declaration.h"
#include "string.h"

extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;

extern int stage;

extern void sample();

void main(void)
{
	int myFlag = 0;

    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    InitFlash();

    InitSysCtrl();//EXternal Oscillator, PLL to 90MHz
    InitGpio();


    InitAdc();
    //InitSci();
    InitEPwm();
    LLC_PwmGenerate();


    DINT;

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = &cpu_timer0_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    PID_Init();

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 90, 50);  //20K
    CpuTimer0Regs.TCR.all = 0x4000;

    IER |= M_INT1;
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM



    for(;;)
    {
    	myFlag = 1 - myFlag;

        COMMU_LED_GPIO = myFlag;

        DELAY_US(500000);


    }
}



