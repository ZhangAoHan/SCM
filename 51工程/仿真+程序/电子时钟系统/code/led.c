#define LED_GLOBAL 1
#include "led.h"
extern void delay(uint us);     //声明延迟函数，实例化在key.c文件中 
extern void delay_us(uint us); 
/********************************************************************************************
* 函数名称：void init_led(void)
* 功    能：led参数初始化
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void init_led(void)
{
   LED = segLedCode[0];
   LED_CS1 = 0;
   LED_CS2 = 0;
   LED_CS3 = 0;
   LED_CS4 = 0;
   LED_CS5 = 0;
   LED_CS6 = 0;
   LED_CS7 = 0;
   LED_CS8 = 0;
}				   
/********************************************************************************************
* 函数名称：void ledWrite(uchar c,uchar n,uchar mod)
* 功    能：led写字符操作
* 入口参数：uchar c,uchar n,uchar mod
* 出口参数：无
*********************************************************************************************/
void ledWrite(uchar c,uchar n,uchar mod)
{
   if(CHARACTER == mod)
	  LED = c; 
   else if(DIGITAL == mod)
	   {
	      if((c - '0') < 0x0a)
		  {
		    LED = segLedCode[c - '0'];
		  } 
		  else
		  {  
			LED = segLedCode[0];
		  }
	   }
   switch(n)				//数码管片选
   {
		case 0x01:
		{
		  LED_CS1 = 0;
		  delay_us(10);
		  LED_CS1 = 1;
		  break;
		}
		case 0x02:
		{
		  LED_CS2 = 0;
		  delay_us(10);
		  LED_CS2 = 1;
		  break;
		}
		case 0x03:
		{
		  LED_CS3 = 0;
		  delay_us(10);
		  LED_CS3 = 1;
		  break;
		}
	    case 0x04:
		{
		  LED_CS4 = 0;
		  delay_us(10);
		  LED_CS4 = 1; 
		  break;
		}
		case 0x05:
		{
		  LED_CS5 = 0;
		  delay_us(10);
		  LED_CS5 = 1;
		  break;
		}
		case 0x06:
		{
		  LED_CS6 = 0;
		  delay_us(10);
		  LED_CS6 = 1;
		  break;
		}
		case 0x07:
		{
		  LED_CS7 = 0;
		  delay_us(10);
		  LED_CS7 = 1;
		  break;
		}
		case 0x08:
		{
		  LED_CS8 = 0;
		  delay_us(10);
		  LED_CS8 = 1;
		  break;
		}
		default:
		  break;

   }

}

/********************************************************************************************
* 函数名称：void ledSweepDisplay(uchar *segCode,uchar segCodeMod)
* 功    能：显示子函数
* 入口参数：*segCode，segCodeMod
* 出口参数：无
*********************************************************************************************/	   	  
void ledSweepDisplay(uchar *segCode,uchar segCodeMod)	    //循环显示子函数 
{
   	uchar segCount;
	for(segCount = 0;segCount < 8;segCount++)
	{
	   if(segCodeMod&0x01)	                                //1代表此处显示任意字符 
	   {
	     ledWrite(segCode[segCount],segCount + 1,CHARACTER); 				   
	   }
	   else
	   {
	     ledWrite(segCode[segCount],segCount + 1,DIGITAL);
	   }
	   segCodeMod = segCodeMod >> 1;
	}
}
