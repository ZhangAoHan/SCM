#define LED_GLOBAL 1
#include "led.h"
code uchar ledCode[10]={0x7e,0x06,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};

/********************************************************
*函数名称：keyDelay_us(uint us)
*函数功能：毫秒级延时函数
*函数入口：延时循环周期数us
*函数出口：无
********************************************************/
void ledDelay_us(uint us)
{
  uchar delayi;
  while(--us)
  {
	for(delayi=0;delayi<10;delayi++);
  } 
}
/*********************************************************
*函数名称：ledInit(void)
*函数功能：数码管显示初始化
*函数入口：无
*函数出口：无
**********************************************************/
void led_init(void)
{
  LED='0';
  LED_CS1=0;
  LED_CS2=0;
  LED_CS3=0;
  LED_CS4=0;
  LED_CS5=0;
  LED_CS6=0;
  LED_CS7=0;
  LED_CS8=0;
}
/**************************************************
*函数名称：ledWrite(uchar c,uchar n)
*函数功能：向第n个数码管写数据c
*函数入口：无
*函数出口：无
**************************************************/
void ledWrite(uchar c,uchar n)
{
   if((c-'0')<0x0a)
   {
	 LED=ledCode[c-'0'];	
     switch(n)
     {
	   case 0x01:
		{
		  LED_CS1=0;
		  ledDelay_us(10);
		  LED_CS1=1;
		  break;
	   }
	  case 0x02:
	   {
		  LED_CS2=0;
		  ledDelay_us(10);
		  LED_CS2=1;
		  break;
	   }
	  case 0x03:
	   {
		  LED_CS3=0;
		  ledDelay_us(10);
		  LED_CS3=1;
		  break;
	   }
	  case 0x04:
	   {
		  LED_CS4=0;
		  ledDelay_us(10);
		  LED_CS4=1; 
		  break;
	   }
	  case 0x05:
	   {
		  LED_CS5=0;
		  ledDelay_us(10);
		  LED_CS5=1;
		  break;
	   }
	  case 0x06	:
	   {
		  LED_CS6=0;
		  ledDelay_us(10);
		  LED_CS6=1;
		  break;
	   }
	  case 0x07:
	   {
		  LED_CS7=0;
		  ledDelay_us(10);
		  LED_CS7=1;
		  break;
	   }
	  case 0x08:
	   {
		  LED_CS8=0;
		  ledDelay_us(10);
		  LED_CS8=1;
		  break;
	   }
	  default:
		 break;

      }
   }	   	   
}
/*******************************************************
*函数名称：ledSweepDisplay(uchar segCode[8])
*函数功能：循环显示8位数码管
*函数入口：
*函数出口：
*******************************************************/
void ledSweepDisplay(uchar *segCode,uchar ledLen)
{
  uchar segCount;
  for(segCount=0;segCount<ledLen;segCount++)
	ledWrite(segCode[segCount],segCount+1);

}