//#include "reg51.h"
#include <STC15F2K60S2.H>

//#define TIMS 3036
//sfr AUXR  =0x8E;
unsigned char i;
void timer_0() interrupt 1
{
//	P46=!P46;
//	P47=!P47;
	i++;
	if(i==10)
	{
		i=0;
	P0=~P0;
	//TR0=0;
	}
}
main()
{
	P0M0=P0M1=0;
//	TL0=(65535-50000)/256;
//	TH0=(65535-50000)%256;
	AUXR&=0x7F;
	TMOD=0x09;
//	P46=0;
//	P47=0;
	P0=0x00;
	TR0=1;
	ET0=1;
	EA=1;
	while(1);
}