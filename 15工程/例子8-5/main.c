#include "reg51.h"
#define TIMS 3036
sfr CLK_DIV=0x97;
sfr IE2 =0xAF;
sfr TH3 =0xD4;
sfr TL3 =0xD5;
sfr T4T3M =0xD1;
void timer_3() interrupt 19
{
	P46=!P46;
	P47=!P47;
}
main()
{
	CLK_DIV=0x03;
	TL3=TIMS;
	TH3=TIMS>>8;
	T4T3M=0x08;
	P46=0;
	P47=0;
	IE2|=0x20;
	EA=1;
	while(1);
}