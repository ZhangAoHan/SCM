#include "reg51.h"
sfr P_SW2    =0xBA;
sfr PWMCFG   =0xF1;
sfr PWMCR    =0xF5;
sfr P2M0     =0x96;
sfr P2M1     =0X95;
unsigned char xdata *PWMCKS;
unsigned char xdata *PWMCH;
unsigned char xdata *PWMCL;
unsigned char xdata *PWM4T1H;
unsigned char xdata *PWM4T1L;
unsigned char xdata *PWM4T2H;
unsigned char xdata *PWM4T2L;
unsigned char xdata *PWM4CR;
void main()
{
	 P2M0=0;
	 P2M1=0;
   P_SW2|=0x80;
	 PWMCFG&=0xFB;
	 PWMCKS=0xFFF2;
	 *PWMCKS=0x03;
	 PWMCH=0xFFF0;
	 PWMCL=0xFFF1;
	 *PWMCH=0;
	 *PWMCL=19;
	 PWM4T1H=0xFF20;
	 PWM4T1L=0xFF21;
	 *PWM4T1H=0;
	 *PWM4T1L=3;
	 PWM4T2H=0xFF22;
	 PWM4T2L=0xFF23;
	 *PWM4T2H=0;
	 *PWM4T2L=0x10;
	 PWM4CR=0xFF24;
	 *PWM4CR=0;
	 P_SW2&=0x0F;
	 PWMCR|=0x84;
}
