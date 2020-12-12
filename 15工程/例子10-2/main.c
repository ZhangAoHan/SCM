#include "reg51.h"
#define FOSC  18432000L
#define BAUD 115200
sfr AUXR  =0x8E;
bit busy=0;
xdata char menu[]={"\r\n--Display Press buttons information--\r\n"};
void IO_KeyDelay(void)
{
	unsigned char i;
	i = 60;
	while(--i)	;
}

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
	unsigned char c1_new,c1_old=0,c1;
	SCON=0x50;
	AUXR=0x40;
	TL1=(65536-((FOSC/4)/BAUD));
	TH1=(65536-((FOSC/4)/BAUD))>>8;
	TR1=1;
	ES=1;
	EA=1;
	 SendString(&menu);
	 while(1){
		 P0=0xF0;
		 IO_KeyDelay();
		 c1_new=P0&0xF0;  
		if(c1_new!=c1_old)
	   	{
				c1_old=c1_new;
		   if(c1_new!=0xF0)
	      {
		      P0=0xFE;
	        IO_KeyDelay();
		      c1_new=P0;	 
		      switch (c1_new)
		       {
			     case 0xee: c1=0;  break;
			     case 0xde:  c1=4;  break;
			     case 0xbe:  c1=8;  break;
			     case 0x7e:  c1=12;  break;
			     default  : ; 
		       }
		      P0=0xFD;
		      IO_KeyDelay();
		      c1_new=P0;	 
		      switch (c1_new)
	      	 {
			     case 0xed: c1=1; break;
			     case 0xdd: c1=5; break;
			     case 0xbd: c1=9; break;
			     case 0x7d: c1=13; break;
			     default  : ; 
		       }
		      P0=0xFB;
		      IO_KeyDelay();
		      c1_new=P0;	 
		      switch (c1_new)
		     {
			    case 0xeb: c1=2; break;
			    case 0xdb: c1=6; break;
			    case 0xbb: c1=10; break;
			    case 0x7b: c1=14; break;
			    default  : ; 
		     }
		 		 P0=0xF7;
		     IO_KeyDelay();
		     c1_new=P0;	 
		     switch (c1_new)
		     {
			     case 0xe7: c1=3; break;
			     case 0xd7: c1=7; break;
			     case 0xb7: c1=11;break;
			     case 0x77: c1=15; break;
			     default  : ; 
		     }
				 SendString("\r\n press #");
				 if(c1<10) 
		        SendData(c1+0x30);
				 else if(c1==10)
				    SendString("10");
				 else if(c1==11)
				    SendString("11");
				 else if(c1==12)
				    SendString("12");
				 else if(c1==13)
				    SendString("13");
				  else if(c1==14)
				    SendString("14"); 
					else if(c1==15)
				    SendString("15");
				 SendString(" button\r\n");
      }
    }
	}
}
	