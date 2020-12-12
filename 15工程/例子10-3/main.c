#include "reg51.h"
#include "intrins.h"
#define FOSC  6000000L
#define BAUD 115200
#define S2RI 0x01
#define S2TI 0x02
sfr AUXR  =0x8E;
sfr AUXR1 =0xA2;
sfr AUXR2 =0x8F;
sfr TH2   =0xD6;
sfr TL2   =0xD7;
sfr S2CON =0x9A;
sfr S2BUF =0x9B;
sfr P3M1  =0xB1;
sfr P3M0  =0xB2;
sfr P_SW2 =0xBA;
sfr IE2   =0xAF;
sbit P36  =P3^6;
bit busy=0;
unsigned char irdata[4]={0,0,0,0};	
bit flag=0;
void SendData(unsigned char dat)
{
	while(busy);
	S2BUF=dat;
	busy=1;
}
void SendString(char *s)
{
	while(*s!='\0')
		SendData(*s++);
}

unsigned int high_level_time()
{
	TL0=0;
	TH0=0;
	TR0=1;
	while(P36==1)
	{
		if(TH0>=0xEE)
			 break;
	}
	TR0=0;
	return(TH0*256+TL0);
}
unsigned int low_level_time()
{
	TL0=0;
	TH0=0;
	TR0=1;
	while(P36==0)
	{
		if(TH0>=0xEE)
			 break;
	}
	TR0=0;
	return(TH0*256+TL0);
}
void int2() interrupt 10
{
	unsigned char i,j;
	unsigned int count=0;
	unsigned char dat=0;
	
	AUXR2&=0x00;
	count=low_level_time();
	
	if(count<4000 || count>5000)
	{
	   return;
	}
	count=high_level_time();
	if(count<2000 || count>2500)
	{
     return;
	}
	
	for(i=0;i<4;i++)
	{ 
   P36=1;
		dat=0;
	   for(j=0;j<8;j++)
		  {
		     count=low_level_time();
				 if(count<250 || count>300) 
            return;
			   count=high_level_time(); 
				 if(count>250 && count<300)
					  dat>>=1;
				 else if(count>800 && count<1000)
				 {
					 dat>>=1;
					 dat|=0x80;
				 }
				 else return;
				
				 
			 }
			 irdata[i]=dat; 	
	 }
	  flag=1;   
	 AUXR2|=0x10;
}

void uart2() interrupt 8
{
	if(S2CON & S2RI)
		S2CON&=~S2RI;
	if(S2CON & S2TI)
	{
		S2CON&=~S2TI;
	  busy=0;
	}
}
		
void main()
{
	unsigned char k;
	P36=1;
	P3M1=0x00;
	P3M0=0x00;
	TMOD=0x00;
	S2CON=0x50;
	AUXR=0x14;
	P_SW2|=0x01;
	TL2=(65536-((FOSC/4)/BAUD));
	TH2=(65536-((FOSC/4)/BAUD))>>8;
	IE2|=0x01;
	AUXR2|=0x10;
	EA=1;
	SendString("\r\n--begin-----\r\n");
	 while(1)
		{
		 if(flag==1)
		 {
			 flag=0;
			    SendString("\r\n--Received IR data is-----\r\n");
			 for(k=0;k<4;k++)
			   SendData(irdata[k]);
			   SendString("\r\n");
			 AUXR2|=0x10;
      }
	 }
 }	