#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,
					 0x6d,0x7d,0x07,0x7f,0x6f,
					 0x77,0x7c,0x39,0x5e,0x79,
					 0x71};
uchar code tab[]={0,1,2,3,4,5,6,7};
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void main()
{
	uint i,j;
	while(1)
	{
		for(i=0;i<16;i++)
		{
			for(j=0;j<8;j++)
			{
				P0=table[i];
				P2=tab[j];
				delay(50);
			}
		}
	}
}
