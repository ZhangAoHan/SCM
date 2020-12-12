#include "reg51.h"
#define FOSC  18432000L
#define BAUD 115200
sfr AUXR  =0x8E;
sfr TH2   =0xD6;
sfr TL2   =0xD7;
bit busy=0;
xdata char menu[]={"\r\n------main menu---------------"
	                 "\r\n     input 1:  Control LED10 "
                   "\r\n     input 2:  Control LED9 "
	                 "\r\n     other  :  Exit Program"
	                 "\r\n------end menu----------------"
            };
	
void SendData(unsigned char dat)
{
	while(busy);
	SBUF=dat;
	busy=1;
}
void SendString(char *s)
{
	while(*s!='\0')
		SendData(*s++);
}
void uart1() interrupt 4
{
	if(RI)
		RI=0;
	if(TI)
		TI=0;
	  busy=0;
}
		
void main()
{
	unsigned char c;
	P46=0;
	P47=0;
	SCON=0x50;
	AUXR=0x14;
	AUXR|=0x01;
	TL2=(65536-((FOSC/4)/BAUD));
	TH2=(65536-((FOSC/4)/BAUD))>>8;
	ES=1;
	EA=1;
	 SendString(&menu);
	 while(1){
		 if(RI==1)
		 {
			 c=SBUF;
			 if(c==0x31)
				   P46=!P46;
			 else if(c==0x32)
				   P47=!P47;
			 else 
			 {
				   SendString("\r\n Exit Program");
			 }
		 }    
	 }
}
	