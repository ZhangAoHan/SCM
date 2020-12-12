#include "reg51.h"
#define value 3906
sfr P_SW1    =0xA2;
sfr CCON     =0xD8;
sfr CMOD     =0xD9;
sfr CL       =0xE9;
sfr CH       =0xF9;
sfr CCAPM0   =0xDA;
sfr CCAP0L   =0xEA;
sfr CCAP0H   =0xFA;
sfr CLK_DIV  =0x97;
sbit CCF0    =CCON^0;
sbit CCF1    =CCON^1;
sbit CR      =CCON^6;
sbit CF      =CCON^7;

void PCA_int() interrupt 7
{
	CCF0=0;
	CL=0;
	CH=0;
	P46=!P46;
	P47=!P47;
}

void main()
{
	P46=0;
	P47=0;
	CLK_DIV=0x07;
	P_SW1=0x00;
	CCON=0;
	CL=0;
	CH=0;
	CMOD=0x00;
	CCAP0L=value;
	CCAP0H=value>>8;
	CCAPM0=0x49;
	CR=1;
	EA=1;
	while(1);
}