#include "reg51.h"

sfr CMPCR1  =0xE6;
sfr CMPCR2  =0xE7;

#define CMPEN  0x80
#define CMPIF  0x40
#define PIE    0x20
#define NIE    0x10
#define PIS    0x08
#define NIS    0x04
#define CMPOE  0x02
#define CMPRES 0x01

#define INVCMPO 0x80
#define DISFLT  0x40
#define LCDTY   0x3F

void cmp_int() interrupt 21
{
	unsigned int i=0;
	P46=!P46;
	CMPCR1 &=~CMPIF;
}
	
void main()
{
	unsigned int j=0;
	P46=0;
	CMPCR1=0;
	CMPCR2=0;
	CMPCR1&=~PIS;
	CMPCR1&=~NIS;
	CMPCR1&=~CMPOE;
	CMPCR2&=~INVCMPO;
	CMPCR2&=~DISFLT;
	CMPCR2&=~LCDTY;
	CMPCR2|=(DISFLT & 0x10);
	CMPCR1|=PIE;
	CMPCR1|=CMPEN;
	EA=1;
	while(1)
	{
		if((CMPCR1 & 0x01)==0)
		{
			 for(j=0;j<30000;j++);
		   P47=!P47;
		}
		else
			P46=1;
	}
}
