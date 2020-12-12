#include <STC15F2K60S2.H>
//#include "reg51.h"
#define TIMS 3036
void timer_0() interrupt 1
{
	P0=!P0;
	//P47=!P47;
}
main()
{
	P0M0=P0M1=0;
	TL0=TIMS;
	TH0=TIMS>>8;
	TMOD=0x04;
	//P46=0;
	P0=0x00;
	TR0=1;
	ET0=1;
	EA=1;
	while(1);
}