/*
 * Global_declaration.h
 *
 *  Created on: 2018年1月19日
 *      Author: comeonbaby1
 */

#ifndef USER_INCLUDE_GLOBAL_DECLARATION_H_
#define USER_INCLUDE_GLOBAL_DECLARATION_H_

#include "LLC.h"

//-----系统初始化，写寄存器等基本函数的外部声明放在这个文件内---------//

//#define Period          563   //80kHz
//#define Period          500   //90kHz
//#define Period          450   //100kHz
#define Period          409   //110kHz

//extern void InitSysCtrl(void);
//extern void InitGpio(void);
//extern void InitAdc(void);
//extern void InitSpi(void);
__interrupt void cpu_timer0_isr(void);
//__interrupt void epwm2_isr(void);
//__interrupt void epwm3_isr(void);
//__interrupt void scia_isr(void);

/*GPIO*/
#define POWER_LED_GPIO      GpioDataRegs.GPADAT.bit.GPIO13
#define FAULT_LED_GPIO      GpioDataRegs.GPADAT.bit.GPIO14
#define COMMU_LED_GPIO      GpioDataRegs.GPADAT.bit.GPIO24
#define Inrush_RELAY_GPIO   GpioDataRegs.GPADAT.bit.GPIO23
#define AUX_RELAY_GPIO      GpioDataRegs.GPADAT.bit.GPIO8
#define RS485_IO1_GPIO      GpioDataRegs.GPADAT.bit.GPIO9
#define RS485_IO2_GPIO      GpioDataRegs.GPADAT.bit.GPIO12
#define PC_OUT1_GPIO        GpioDataRegs.GPADAT.bit.GPIO27
#define PC_OUT2_GPIO        GpioDataRegs.GPADAT.bit.GPIO26
#define PC_OUT3_GPIO        GpioDataRegs.GPADAT.bit.GPIO3
#define PC_OUT4_GPIO        GpioDataRegs.GPADAT.bit.GPIO2

#define PC_IN1_GPIO         GpioDataRegs.GPADAT.bit.GPIO1
#define PC_IN2_GPIO         GpioDataRegs.GPADAT.bit.GPIO0
#define Addrs1_GPIO         GpioDataRegs.GPADAT.bit.GPIO22
#define Addrs2_GPIO         GpioDataRegs.GPBDAT.bit.GPIO32
#define Addrs3_GPIO         GpioDataRegs.GPBDAT.bit.GPIO33

/*GPIO actions defines*/
#define POWER_ON            POWER_LED_GPIO = 1; // High enable
#define SOFT_END            Inrush_RELAY_GPIO = 1; // High enable


//struct AD_EN_bits{
//	unsigned int a:1;
//	unsigned int b:1;
//	unsigned int c:1;
//	unsigned int rsvd:13;
//};
//
//union AD_EN_REG{
//	unsigned int all;
//	struct AD_EN_bits bit;
//};

//定义PID控制器
struct PIDREG
{
	float Input;
	float PreInput;
	float Output;
	float PreOutput;
	float Kp;
	float Ki;
	float Kd;
    float Ts;
    float MaxOutput;
	float MinOutput;
};

struct FilterREG
{
    float Input;
    float PreInput;
    float Output;
    float PreOutput;
    float Tc;
    float Ts;
};

struct Fualt_limits{
	float VoltageBat_UL;     //upper limits
	float VoltageBat_LL;     //lower limits
	float Voltage400V_UL;
	float VoltageBUS_UL;
	float CurrentTr_UL;
	float CurrentLr_UL;
	float CurrentLm_UL;
	float CurrentLbb_UL;
};

struct Fault_bits{
	unsigned int OverVoltageBat:1;		// 错误代码 1-01 bit
	unsigned int UnderVoltageBat:1;		// 错误代码 1-02 bit
	unsigned int OverVoltage400V:1;		// 错误代码 1-01 bit
	unsigned int OverVoltageBUS:1;		// 错误代码 1-01 bit
	unsigned int OverCurrentTr:1;		// 错误代码 1-03 bit
	unsigned int OverCurrentLr:1;		// 错误代码 1-04 bit
	unsigned int OverCurrentLm:1;		// 错误代码 1-05 bit
	unsigned int OverCurrentLbb:1;		// 错误代码 1-06 bit
	unsigned int rsvd:8;
};

union Fault_BOOST_REG{
	unsigned int all;
	struct Fault_bits bit;
};

struct Control_bits{
	unsigned int data:12;
	unsigned int add:4;

};

union Control_REG{
	unsigned int all;
	struct Control_bits bit;
};

struct Control_RAM{
	union Control_REG checkcpld;
	union Control_REG test;
	union Control_REG pulsewidth;
	union Control_REG frequency;
};


extern union Fault_BOOST_REG Fault_BOOST;

extern float V_24V;      //voltage sample for 24V bus
extern float IOUT;
extern float IBUS;
extern float T_SR;




void RAM_Add_Init(void);
void PID_Init(void);

extern void sci_send(int c);
extern void sci_send_string(char *msg);


#endif /* USER_INCLUDE_GLOBAL_DECLARATION_H_ */
