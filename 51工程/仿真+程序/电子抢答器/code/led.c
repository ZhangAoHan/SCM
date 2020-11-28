#define LED_GLOBAL 1
#include "led.h"
extern void delay(uint us);     //声明延迟函数，实例化在key.c文件中 
extern void delay_us(uint us); 
/******************************************************************************
* 函数名称:
* 功    能:
* 入口参数:
* 出口参数:
********************************************************************************/
void init_led(void)
{
   LED=segLedCode[0];
   LED_CS1=0;
   LED_CS2=0;
   LED_CS3=0;
   LED_CS4=0;
}	  
/******************************************************************************
* 函数名称:
* 功    能:
* 入口参数:
* 出口参数:
********************************************************************************/
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
		  delay_us(10);
		  LED_CS1=1;
		  break;
		}
		case 0x02:
		{
		  LED_CS2=0;
		  delay_us(10);
		  LED_CS2=1;
		  break;
		}
		case 0x03:
		{
		  LED_CS3=0;
		  delay_us(10);
		  LED_CS3=1;
		  break;
		}
	    case 0x04:
		{
		  LED_CS4=0;
		  delay_us(10);
		  LED_CS4=1; 
		  break;
		}
		default:
		  break;

   }

} 
/******************************************************************************
* 函数名称:
* 功    能:
* 入口参数:
* 出口参数:
********************************************************************************/
	   	  
void ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber) 
{											//循环显示子函数
   	uchar segCount;
	for(segCount=0;segCount<segNumber;segCount++)
	{
	   if(segCodeMod&0x01)	               //1代表此处显示任意字符
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
