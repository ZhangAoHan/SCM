#define LED_GLOBAL 1
#include "led.h"
void ledDelay(uint ms)  
{
   uchar delayi;
   while(--ms)
   {
	 for(delayi=0;delayi<124;delayi++);
   }
}
void init_led(void)
{
   LED=segLedCode[0];
   LED_CS1=0;
   LED_CS2=0;
   LED_CS3=0;
   LED_CS4=0;
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
		  LED_CS1=0;
		  ledDelay(10);
		  LED_CS1=1;
		  break;
		}
		case 0x02:
		{
		  LED_CS2=0;
		  ledDelay(10);
		  LED_CS2=1;
		  break;
		}
		case 0x03:
		{
		  LED_CS3=0;
		  ledDelay(10);
		  LED_CS3=1;
		  break;
		}
	    case 0x04:
		{
		  LED_CS4=0;
		  ledDelay(10);
		  LED_CS4=1; 
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
	   if(segCodeMod&0x01)	   //1代表此处显示任意字符 *
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
