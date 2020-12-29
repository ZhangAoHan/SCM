#define LED_GLOBAL 1
#include "led.h"
extern void delay_us(uint us);                   /*声明微秒级延时函数*/
/****************************************************
*函数名称：led_init(void)
*函数功能：数码管初始化
*函数入口：无
*函数出口：无
****************************************************/
void led_init(void)
{
  //数码管显示pwm初始化值，1/100
  ledWrite('1',0x01,DIGITAL);  
  ledWrite('0',0x02,DIGITAL);
  ledWrite('0',0x03,DIGITAL);
}	       
/***********************************************************
*函数名称：ledWrite(uchar c,uchar n,uchar mod)
*函数功能：向第n个数码管写mod模式的内容c
*函数入口：c为要显示的内容,显示数字时,调用入口应输入数字字符;
n为要显示的数码管编号;mod为要显示的模式
*函数出口：无
*************************************************************/             
void ledWrite(uchar c,uchar n,uchar mod)
{
  if(CHARACTER==mod)  //为任意字段显示
    LED=c;
  else if(DIGITAL==mod)
         LED=segLedCode[c-'0'];
   switch(n)
   {
     case 0x01:
	  {
	    LED_CS1=CS_FORCE_VALUE;
	    delay_us(10);
	    LED_CS1=0;    //~CS_FORCE_VALUE
		break;
	  }
	 case 0x02:
	  {
	   	LED_CS2=CS_FORCE_VALUE;
	    delay_us(10);
	    LED_CS2=0;
		break;
	  }
	 case 0x03:
	  {
	    LED_CS3=CS_FORCE_VALUE;
	    delay_us(10);
	    LED_CS3=0;
		break;
	  }
	 default:
	   break;
   }
}