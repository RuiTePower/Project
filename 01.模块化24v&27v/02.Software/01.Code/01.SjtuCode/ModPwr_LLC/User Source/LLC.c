/*
 * LLC.c
 *
 *  Created on: 2018年2月3日
 *      Author: caoyu
 */

#include "DSP28x_Project.h"
//#include "cmath.h"
#include "Global_declaration.h"


#define Period          409
#define LLC_PWM_TIMER_TBPRD 455
#define DEAD_TIME 45



Uint16 g_usLlcSwitchDuty;		// 原边占空比
//Uint16 g_usLlcSeconDuty;		// 副边占空比
Uint16 g_usLlcSwitchFreq;		// 开关频率
Uint16 g_usDeadBand,g_usPhaseShift,g_usPhaseShiftCalc;


/*
 * g_freq:frequency of pwm,which:which pwm
 *
 * which:LLC_PWM,SR12,OUTAB
 *
 * eg:LLC_PwmSetFreq(50000,OUTAB)
 *
 */
void LLC_PwmSetFreq(Uint16 g_freq,int which){
    int r_freq=90000000/g_freq;
    switch(which){
    case 0:
        EALLOW;
        EPwm1Regs.TBPRD=r_freq;
        EPwm1Regs.CMPA.half.CMPA=r_freq/2;
        EPwm1Regs.TBCTR=0;
        EDIS;
        break;
    case 1:
        EALLOW;
        EPwm3Regs.TBPRD=r_freq;
        EPwm3Regs.CMPA.half.CMPA=r_freq/2;
        EPwm3Regs.TBCTR=0;
        EDIS;
        break;
    case 2:
        EALLOW;
        EPwm4Regs.TBPRD=r_freq;
        EPwm4Regs.CMPA.half.CMPA=r_freq/2;
        EPwm5Regs.TBPRD=r_freq;
        EPwm5Regs.CMPA.half.CMPA=r_freq/2;
        EPwm4Regs.TBCTR=0;
        EPwm5Regs.TBCTR=0;
        EDIS;
        break;
    default:
        break;
    }
}

/*
 *
 */

void LLC_PwmSetPhase(Uint16 g_phase){
    EPwm3Regs.TBPHS.half.TBPHS=g_phase;
}

void LLC_PwmGenerate(void){
    g_usPhaseShiftCalc=Period;
    if(g_usPhaseShiftCalc < LLC_PWM_TIMER_TBPRD)
    {
        g_usPhaseShiftCalc = LLC_PWM_TIMER_TBPRD;
    }
    g_usDeadBand = ((g_usPhaseShiftCalc  - LLC_PWM_TIMER_TBPRD) + DEAD_TIME);
    g_usPhaseShift = (g_usPhaseShiftCalc  - LLC_PWM_TIMER_TBPRD);


    EPwm1Regs.DBRED = g_usDeadBand;
    EPwm1Regs.DBFED = g_usDeadBand;

    EPwm1Regs.TBPHS.half.TBPHS = 0;
    EPwm2Regs.TBPHS.half.TBPHS = g_usPhaseShift;

}


