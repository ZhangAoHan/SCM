#include "reg51.h"
#include "spi.h"
unsigned char code t_display[16]={0x3F,0x06,0x5B,0x4F,
	                              0x66,0x6D,0x7D,0x07,
	                              0x7F,0x6F,0x77,0x7C,
	                              0x39,0x5E,0x79,0x71};
unsigned char code T_COM[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
bit flag=0;
unsigned m=0;
void SPI_SendByte(unsigned char dat)
{
	SPSTAT=SPIF+WCOL;
	SPDAT=dat;
	while((SPSTAT & SPIF)==0);
	SPSTAT=SPIF+WCOL;
}

void seg7scan(unsigned char index1,unsigned char index2)
{
	SPI_SendByte(~T_COM[index1]);
	SPI_SendByte(t_display[index2]);
	HC595_RCLK=1;
	HC595_RCLK=0;
}
void timer_0() interrupt 1
{
	flag=1;	
}
void timer_1() interrupt 3
{
	P46=!P46;
	m++;
	if(m==16) m=0;
}
void main()
{
	unsigned char i=0;
	SPCTL=(SSIG<<7)+(SPEN<<6)+(DORD<<5)+(MSTR<<4)
	     +(CPOL<<3)+(CPHA<<2)+SPEED_4;
	CLK_DIV=0x03;
	TL0=TIMS;
	TH0=TIMS>>8;
	TL1=TIMS1;
	TH1=TIMS1>8;
	AUXR&=0x3F;
	AUXR1=0X08;
	TMOD=0x00;
	TR0=1;
	TR1=1;
	ET0=1;
	ET1=1;
	EA=1;
	
	while(1)
	{
		if(flag==1)
		{
		  flag=0;
		   for(i=0;i<8;i++)
			   {
	       seg7scan(i,(m+i)%16);
					
		     }		
		 }
	}
}