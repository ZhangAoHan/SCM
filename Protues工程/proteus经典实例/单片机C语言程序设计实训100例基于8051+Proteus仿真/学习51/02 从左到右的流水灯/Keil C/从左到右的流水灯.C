#include<reg52.h>
#include<intrins.h>
#include<math.h>
#include<stdio.h>
#define uchar unsigned char
#define uint  unsigned int
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
	   for(y=110;y>0;y--);
}
void main()
{	
	uchar aa;
	P0=0xfc;
	while(1)
		{
		delay(500);
		aa=P0;
		aa=_crol_(aa,1);
		P0=aa;
		}
}
