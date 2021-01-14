#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit ledns_re=P1^0;
sbit ledns_ge=P1^1;
sbit ledns_ye=P1^2;
sbit ledwe_re=P1^3;
sbit ledwe_ge=P1^4;
sbit ledwe_ye=P1^5;
void delay(uchar z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);	
}
void main()
{
	uint i;
	while(1)
	{
		ledns_re=0;
		ledwe_ge=0;
		ledns_ye=1;
		ledwe_ye=1;
		for(i=0;i<50;i++)
		{
			delay(1000);
		}
		ledns_ye=0;
		ledwe_ye=0;
		ledns_re=1;
		ledwe_ge=1;
		for(i=0;i<10;i++)
		{
			delay(1000);
		}
		ledns_ge=0;
		ledwe_re=0;
		ledns_ye=1;
		ledwe_ye=1;
		for(i=0;i<30;i++)
		{
			delay(1000);
		}
		ledns_ye=0;
		ledwe_ye=0;
		ledns_ge=1;
		ledwe_re=1;
		for(i=0;i<10;i++)
		{
			delay(1000);
		}
	}
}
