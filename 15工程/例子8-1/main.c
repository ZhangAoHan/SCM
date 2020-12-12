#include "reg51.h"
#define TIMS 3036
sfr AUXR  =0x8E;
sfr AUXR2 =0x8F;
sfr CLK_DIV=0x97;
void timer_0() interrupt 1
{
	P46=!P46;
	P47=!P47;
}
main()
{
	CLK_DIV=0x03;
	TL0=TIMS;
	TH0=TIMS>>8;
	AUXR&=0x7F;
	AUXR2|=0x01;
	TMOD=0x00;
	P46=0;
	P47=0;
	TR0=1;
	ET0=1;
	EA=1;
	while(1);
}