#include "reg51.h"
#define TIMS 3036
sfr AUXR  =0x8E;
sfr IE2 =0xAF;
sfr TH2 =0xD6;
sfr TL2 =0xD7;
sfr CLK_DIV=0x97;
void timer_2() interrupt 12
{
	P46=!P46;
	P47=!P47;
}
main()
{
	CLK_DIV=0x03;
	TL2=TIMS;
	TH2=TIMS>>8;
	AUXR|=0x10;
	P46=0;
	P47=0;
	IE2|=0x04;
	EA=1;
	while(1);
}