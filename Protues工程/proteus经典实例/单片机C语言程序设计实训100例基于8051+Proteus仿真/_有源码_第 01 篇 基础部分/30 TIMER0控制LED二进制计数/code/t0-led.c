#include <reg52.h>

void main()
{
 	TMOD = 0x05;
	TH0 = 0x00;
	TL0 = 0x00;
	TR0 = 1;
	while(1)
	{
	 	P1 = TH0;
		P2 = TL0;
	}
}