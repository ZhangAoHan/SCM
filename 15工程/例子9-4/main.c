//#include "reg51.h"

#include <STC15F2K60S2.H>

#define value 3906
//sfr P_SW1    =0xA2;
//sfr CCON     =0xD8;
//sfr CMOD     =0xD9;
//sfr CL       =0xE9;
//sfr CH       =0xF9;
//sfr CCAPM0   =0xDA;
//sfr CCAP0L   =0xEA;
//sfr CCAP0H   =0xFA;
//sfr PCA_PWM0 =0xf2;
//sbit CCF0    =CCON^0;
//sbit CCF1    =CCON^1;
//sbit CR      =CCON^6;
//sbit CF      =CCON^7;
//unsigned char i=0;
//void PCA_int() interrupt 7
//{
//	CF=0;
//	CCAP0H=i;
//	CCAP0L=i;
//	if(i<255) i++;
//  else i=0;		

//}
void main()
{
//	CLK_DIV=0x03;
	P_SW1=0x00;
	CCON=0;
	CL=0;
	CH=0;
	CMOD=0x02;
	PCA_PWM0=0x00;
	CCAP0L=0x10;
	CCAP0H=0x10;
	CCAPM0=0x42;
	CR=1;
	EA=1;
//	while(1);
}