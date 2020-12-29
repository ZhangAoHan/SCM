#include "sin.h"
double  sinInterTime;
void main()
{
  sinInterTime=(1000UL)/(SIN_FRE*SIN_SEG);     //根据正弦波频率计算定时器0延时时间
  timer0_init(sinInterTime);				   //初始化定时器0
  dac0832_init();                          	   //dac0832初始化
  sei();
  while(1);
}
/***************************************************
*函数名称：Timer0_Sin(void)
*函数功能：timer0中断入口,此时输出采样数据
*函数入口：无
*函数出口：无
****************************************************/
void Timer0_Sin(void) interrupt 1
{											
   TH0=timer0TH0;        //数据重写入
   TL0=timer0TL0;
    
   if(sinCodeCount<128)
    {
	  writeDAC0832(Sin[sinCodeCount]);
	  sinCodeCount+=SIN_SPACING; 
	}
	else
	{
	  sinCodeCount=0;
	  writeDAC0832(Sin[sinCodeCount]);
	}
	sei();
       
}