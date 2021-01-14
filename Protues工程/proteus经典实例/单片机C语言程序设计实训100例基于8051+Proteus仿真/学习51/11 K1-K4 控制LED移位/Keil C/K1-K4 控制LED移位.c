#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit s1=P1^4;
sbit s2=P1^5;
sbit s3=P1^6;
sbit s4=P1^7;
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void keycan()
{
	uint i;
	if(s1==0)
	{
		delay(30);
		if(s1==0)
		{
			i++;
			switch(i)
			{
				case 1:
						P0=0x7f;
						break;
				case 2:
						P0=0xbf;
						break;
				case 3:
						P0=0xdf;
						break;
				case 4:
						P0=0xef;
						break;
				case 5:
						P0=0xf7;
						break;
				case 6:
						P0=0xfb;
						break;
				case 7:
						P0=0xfd;
						break;
				case 8:
						P0=0xfe;
						break;
				default:i=0;
			}
			while(!s1);
		}
	}
	if(s2==0)
	{
		delay(30);
		if(s2==0)
		{
			i++;
			switch(i)
			{
				case 1:
						P0=0xfd;
						break;
				case 2:
						P0=0xfb;
						break;
				case 3:
						P0=0xf7;
						break;
				case 4:
						P0=0xef;
						break;
				case 5:
						P0=0xdf;
						break;
				case 6:
						P0=0xbf;
						break;
				case 7:
						P0=0x7f;
						break;
				case 8:
						P0=0xfe;
						break;
				default:i=0;
			}
		while(!s2);
		}
	}
}
void keycan1()
{
	uint i;
	if(s3==0)
	{
		delay(30);
		if(s3==0)
		{
			i++;
			switch(i)
			{
				case 1:
						P2=0x7f;
						break;
				case 2:
						P2=0xbf;
						break;
				case 3:
						P2=0xdf;
						break;
				case 4:
						P2=0xef;
						break;
				case 5:
						P2=0xf7;
						break;
				case 6:
						P2=0xfb;
						break;
				case 7:
						P2=0xfd;
						break;
				case 8:
						P2=0xfe;
						break;
				default:i=0;
			}
			while(!s3);
		}
	}
	if(s4==0)
	{
		delay(30);
		if(s4==0)
		{
			i++;
			switch(i)
			{
				case 1:
						P2=0xfd;
						break;
				case 2:
						P2=0xfb;
						break;
				case 3:
						P2=0xf7;
						break;
				case 4:
						P2=0xef;
						break;
				case 5:
						P2=0xdf;
						break;
				case 6:
						P2=0xbf;
						break;
				case 7:
						P2=0x7f;
						break;
				case 8:
						P2=0xfe;
						break;
				default:i=0;
			}
			while(!s4);
		}
	}
}
void main()
{
	P0=0xfe;
	P2=0xfe;
	while(1)
	{
		keycan();
		keycan1();
	}
}
