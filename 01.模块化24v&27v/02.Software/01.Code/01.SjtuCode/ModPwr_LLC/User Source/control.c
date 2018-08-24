/*
 * control.c
 *
 *  Created on: 2018Äê1ÔÂ19ÈÕ
 *      Author: comeonbaby1
 */

#include "DSP28x_Project.h"
//#include "cmath.h"
#include "Global_declaration.h"

int stage=0;
int soft_cnt=0;
extern int cpuflag;
int order = 1;
Uint32  PassCount=0;

int count_up_down = 1;
Uint16 pulsewidth = 240;
Uint16 frequency = 0;
Uint16 frequency1 = 426;
Uint16 usDeadBand,usPhaseShift;

int sample_cnt=0;
int sample_flag=0;
Uint16 AdcaResults[8] = {0, 0, 0, 0, 0, 0, 0, 0};        //ADC_IN_A0  TO  ADC_IN_A7
Uint16 AdcbResults[8] = {0, 0, 0, 0, 0, 0, 0, 0};        //ADC_IN_B0  TO  ADC_IN_B7

Uint16 a;

Uint16 sdata;  // send data
Uint16 rdata;  // received data
union Fault_BOOST_REG	STATE;
struct Control_RAM Control_CPLD;
struct PIDREG PID_TEST;
struct PIDREG *PID_24V;

int k = 0;
int overvoltage_count = 0;
int OV_inflag = 0;
int OI_inflag = 0;
int OT_flag = 0;
int protect = 0;
int fan = 1;
int fanstate_SR = 1;
int fanstate_Boost = 1;

float V_24V_In = 0;      //voltage sample for 24V inner bus
float V_24V_Out = 0;
float IOUT = 0;
float IBUS = 0;
float T_SR = 0;

float Input1 = 0;
float PreInput1 = 0;
float Output1 = 0;
float PreOutput1=0;
float Kp1=0.2;
float Ki1=50000;
float Kd1=0;
float Ts1=0.00005;
float MaxOutput1=40;
float MinOutput1=-40;

void sci_send(int c);
void sci_send_string(char *msg);
void soft_start();
void fanstate();

void RAM_Add_Init(void){
	Control_CPLD.checkcpld.bit.add = 0;
	Control_CPLD.test.bit.add = 1;
	Control_CPLD.pulsewidth.bit.add = 8;
	Control_CPLD.frequency.bit.add = 9;
}

void sample(void){

	AdcRegs.ADCSOCFRC1.all= 0x0FFF;

	//a=AdcResult.ADCRESULT1;

	while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0);
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
	AdcaResults[2] = AdcResult.ADCRESULT0;
	AdcaResults[3] = AdcResult.ADCRESULT1;
	AdcaResults[4] = AdcResult.ADCRESULT2;
	AdcaResults[5] = AdcResult.ADCRESULT3;
    AdcaResults[6] = AdcResult.ADCRESULT4;
    AdcaResults[7] = AdcResult.ADCRESULT5;

    AdcbResults[0] = AdcResult.ADCRESULT6;
    AdcbResults[1] = AdcResult.ADCRESULT7;
    AdcbResults[2] = AdcResult.ADCRESULT8;
    AdcbResults[3] = AdcResult.ADCRESULT9;
    AdcbResults[4] = AdcResult.ADCRESULT10;
    AdcbResults[5] = AdcResult.ADCRESULT11;

}

void convert(void){
	  //actual value
    //T_SR = 37741.9355/(AdcbResults[5]-4095) + 27.264332;
    V_24V_Out = AdcbResults[5] * 0.01322 - 0.21766;
    V_24V_In = AdcbResults[5] * 0.007446 - 0.34282;
//    if(AdcbResults[2] <= 730)
//    {
//        IOUT = AdcbResults[0]*0.051165+1.5345;
//        IBUS = AdcbResults[2]*0.051165+1;
//    }
//    else
//    {
//        IOUT = AdcbResults[0]*0.051165+1.5345;
//        IBUS = AdcbResults[2]*0.051165+4;
//    }
}

void faultcheck(void){

//	if(V_400V > 220){
//		Fault_BOOST.bit.OverVoltage400V = 1;
//		overvoltage_count=1;
//		if(overvoltage_count > 200){
//			GPIO_WritePin(DCDC_ON_GPIO, 1);
//		}
//	}
//	else{
//		overvoltage_count = 0;
//	}
}

void rstPID(struct PIDREG *Pid){
	 Pid->Input = 0;
	 Pid->Output = 0;
	 Pid->PreInput = 0;
	 Pid->PreOutput = 0;
}

void PidCal(struct PIDREG *Pid)
{
    Pid->Output=Pid->Kp*(Pid->Input-Pid->PreInput)+Pid->Ki*Pid->Input*Pid->Ts+Pid->PreOutput;
    if(Pid->Output>Pid->MaxOutput)
        Pid->Output=Pid->MaxOutput;
    if(Pid->Output<Pid->MinOutput)
        Pid->Output=Pid->MinOutput;
    Pid->PreOutput=Pid->Output;
    Pid->PreInput=Pid->Input;
}

void PID_Init(void){
	PID_24V=&PID_TEST;

    rstPID(PID_24V);

	PID_24V->MaxOutput = 40.0;
	PID_24V->MinOutput = -40.0;

	PID_24V->Kp = 0.2;
	PID_24V->Ki = 5000.0;
	PID_24V->Kd = 0.0;
	PID_24V->Ts = 0.00005;
}


// cpu_timer0_isr - CPU Timer0 ISR with interrupt counter
#pragma CODE_SECTION(cpu_timer0_isr, "ramfuncs");

__interrupt void cpu_timer0_isr(void)
{
   //static Uint16 xdata;
   //static Uint16 rdata;
	CpuTimer0.InterruptCount++;
   //sample and protect
   sample();                //AD sample
   convert();
   faultcheck();

   //close loop control
   PID_24V->Input = (float)(24.0 - V_24V_Out);
   PidCal(PID_24V);
   pulsewidth = (Uint16)(240.0 + PID_24V->Output);

   if(pulsewidth >= 281) pulsewidth = 281;
   if(pulsewidth <= 204) pulsewidth = 204;


//
//   if(protect == 1)
//   {
//       EALLOW;
//
//       EPwm1Regs.TZFRC.bit.OST = 1;
//       EPwm2Regs.TZFRC.bit.OST = 1;
//
//       EDIS;
//   }


    //frequency test
//    if (count_up_down == 0) pulsewidth = pulsewidth - 1;
//    else pulsewidth = pulsewidth + 1;
//
//    if(pulsewidth == 281) count_up_down = 0;
//    if(pulsewidth == 204) count_up_down = 1;
//
//    //pulsewidth = 240;
    //frequency test

    frequency = pulsewidth * 2;

    EPwm1Regs.TBPRD = frequency;
    EPwm1Regs.CMPA.half.CMPA = pulsewidth;

    EPwm2Regs.TBPRD = frequency;
    EPwm2Regs.CMPA.half.CMPA = pulsewidth;

    if(frequency < 450)
    {
        frequency = 450;
    }
    usDeadBand = ((frequency  - 450) + 45);
    usPhaseShift = (frequency  - 450);

    EPwm1Regs.DBRED = usDeadBand;
    EPwm1Regs.DBFED = usDeadBand;

    EPwm1Regs.TBPHS.half.TBPHS = 0;
    EPwm2Regs.TBPHS.half.TBPHS = usPhaseShift;

   // Acknowledge this interrupt to receive more interrupts from group 3

   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1 ;
}


void sci_send(int c){
	while(ScibRegs.SCICTL2.bit.TXRDY != 1) {}
	ScibRegs.SCITXBUF = c;
}

void sci_send_string(char *msg){
	int i;
	i = 0;
	while('\0' != msg[i])
	{
		sci_send(msg[i]);
	    i++;
	}
}

void soft_start(){

}

