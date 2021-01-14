#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int 
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,
					 0x6d,0x7d,0x07,0x7f,0x6f};
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void main()
{
	uint i;
	for(i=0;i<10;i++)
	{
		P2=table[i];
		delay(500);
	}
}
