#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int 
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void main()
{
	uint temp;
	P1=0xff;
	while(1)
	{
		
		temp=P1 & 0xff;
		P0=temp;
		delay(10);
		P1=0xff;
	}
}
