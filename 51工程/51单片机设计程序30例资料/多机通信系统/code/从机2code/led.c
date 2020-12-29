#define LED_GLOBAL 1
#include "led.h"
/****************************************************
*函数名称：led_init(void)
*函数功能：数码管初始化
*函数入口：无
*函数出口：无
****************************************************/
void led_init(void)
{
  LED=segLedCode[0];
  LED_CS1=CS_FORCE_VALUE;   //锁存器向LED数据口输出数据
  delay_us(10);
  LED_CS1=~CS_FORCE_VALUE;  //锁存器数据端口数据保持
}	       
/***********************************************************
*函数名称：ledWrite(uchar c,uchar n,uchar mod)
*函数功能：向第n个数码管写mod模式的内容c
*函数入口：c为要显示的内容,显示数字时,调用入口应输入数字字符;
n为要显示的数码管编号;mod为要显示的模式
*函数出口：无
*说明：由于本实例为一个数码管显示，故调用函数时n应映射为0x01
*************************************************************/             
void ledWrite(uchar c,uchar n,uchar mod)
{
  if(CHARACTER==mod)  //为任意字段显示
    LED=c;
  else if(DIGITAL==mod)
         LED=segLedCode[c-'0'];
  if(n==0x01)
  {
    LED_CS1=CS_FORCE_VALUE;
	delay_us(10);
	LED_CS1=~CS_FORCE_VALUE;
  }
}
/****************************************************
*函数名称：delay_us(uint us)
*函数功能：微秒级延时函数
*函数入口：us,延时数量
*函数出口：无
****************************************************/               
void delay_us(uint us)
{
  uchar delayi;
  while(--us)
  {
	for(delayi=0;delayi<10;delayi++);
  } 
}