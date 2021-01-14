#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int 
sbit s1=P1^0;
sbit out=P2^4;
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void main()
{
	out=1;
	while(1)
	{
		if(s1==0)
		{
			delay(30);
			if(s1==0)
			{
				out=~out;
			}
		}
	}
}
