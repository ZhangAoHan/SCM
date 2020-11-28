#define LED_GLOBAL 1
#include "led.h"
void delay(uint ms)
{
   uchar delayi;
   while(--ms)
   {
	 for(delayi=0;delayi<124;delayi++);
   }
}     
void delay_us(uint us)
{
  uchar delayi;
   while(--us)
   {
	 for(delayi=0;delayi<10;delayi++);
   } 
}
void init_led(void)
{
   LED=segLedCode[0];
   LED_CS1=LED_FORCE_VALUE;
   LED_CS2=LED_FORCE_VALUE;
   LED_CS3=LED_FORCE_VALUE;
   LED_CS4=LED_FORCE_VALUE;
}
void ledWrite(uchar c,uchar n,uchar mod)
{
   if(CHARACTER==mod)
   {
	  LED=c;  
   }
   else if(DIGITAL==mod)
	   {
	      if((c-'0')<0x0a)
		  {
		    LED=segLedCode[c-'0'];
		  } 
		  else
		  {  
			LED=segLedCode[0];
		  }
	   }
   switch(n)
   {
		case 0x01:
		{
		  LED_CS1=LED_FORCE_VALUE;
		  delay_us(10);
		  LED_CS1=~LED_FORCE_VALUE;
		  break;
		}
		case 0x02:
		{
		  LED_CS2=LED_FORCE_VALUE;
		  delay_us(10);
		  LED_CS2=~LED_FORCE_VALUE;
		  break;
		}
		case 0x03:
		{
		  LED_CS3=LED_FORCE_VALUE;
		  delay_us(10);
		  LED_CS3=~LED_FORCE_VALUE;
		  break;
		}
	    case 0x04:
		{
		  LED_CS4=LED_FORCE_VALUE;
		  delay_us(10);
		  LED_CS4=~LED_FORCE_VALUE; 
		  break;
		}
		default:
		  break;

   }

}
	   	  
void ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber)	    //循环显示子函数
{
   	uchar segCount;
	for(segCount=0;segCount<segNumber;segCount++)
	{
	   if(segCodeMod&0x01)	           //1代表此处显示任意字符
	   {
	     ledWrite(segCode[segCount],segCount+1,CHARACTER); 
	   }
	   else
	   {
	     ledWrite(segCode[segCount],segCount+1,DIGITAL);
	   }
	   segCodeMod=segCodeMod>>1;
	}
}
