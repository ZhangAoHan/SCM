#include<reg52.h>
#include<intrins.h>
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
	uint led,i;
	led=0x01;
while  (1)
	{
	for(i=0;i<8;i++)
	{
		P2=led;
		delay(500);
		led<<=1;
	}
	for(i=8;i>0;i--)
	{
		P2=led;
		delay(500);
		led>>=1;
	}
	}
}
