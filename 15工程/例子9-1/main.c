#include <STC15F2K60S2.H>
//#include "reg51.h"

//sfr P_SW1    =0xA2;
//sfr CCON     =0xD8;
//sfr CMOD     =0xD9;
//sfr CL       =0xE9;
//sfr CH       =0xF9;
//sfr CCAPM0   =0xDA;
//sbit CCF0    =CCON^0;
//sbit CCF1    =CCON^1;
//sbit CR      =CCON^6;
//sbit CF      =CCON^7;

void PCA_int() interrupt 7
{
	CCF0=0;
	P0=~P0;
	//P47=!P47;
}

void main()
{
	P0M0=P0M1=0;
	P0=0;
//	P47=0;
	P_SW1=0x00;
	CCON=0;
	CL=0;
	CH=0;
	CMOD=0x00;
	CCAPM0=0x11;
	CR=1;
	EA=1;
	while(1);
}