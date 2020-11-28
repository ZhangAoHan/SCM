/****************************************************
*实例名称：秒表
*实例说明：本实例实现0.01S~59分的计时。按下Start键时
开始计数,此时按下Stop键时停止计时,按下Clear键时清零
显示屏。Start键和Stop键分别通过外部中断0和外部中断1来
实现操作
*作者：kxm
*时间：09.06.13
****************************************************/
#include "target.h"
#include "led.h"
/*时钟显示数字区,从左至右为:分高位,分低位;秒高位,秒低位;毫秒高位,毫秒低位*/
uchar clock_time[8]={'0','0',0x01,'0','0',0x01,'0','0'};
const uchar displayMode=0x24;
void main()
{
  uchar i;
  target_init();
  led_init();
  sei();
  while(1)
  {
   if(CLEAR_KEY==0)
   {
     for(i=0;i<200;i++);
	 if(CLEAR_KEY==0)
	 {
	   clock_time[MS_H]='0';
	   clock_time[MS_L]='0';
	   clock_time[S_H]='0';
	   clock_time[S_L]='0';
	   clock_time[MIN_H]='0';
	   clock_time[MIN_L]='0';
	 }
   }
   ledSweepDisplay(clock_time,displayMode,0x08); 
  }
}
void T0_OverFlow(void) interrupt 1 //定时器0溢出中断,延时10ms
{
  TH0=0xDC;
  TL0=0x00;
  if(clock_time[MS_L]<'9')
    clock_time[MS_L]++;
  else
   {
     clock_time[MS_L]='0';
	 if(clock_time[MS_H]<'9')
	  clock_time[MS_H]++;
	 else
	 {
	   clock_time[MS_H]='0';
	   ms_to_s(clock_time);
	 }
   }
}
void StartInt(void) interrupt 0	  //启动按键通过外部中断0
{
  TR0=1;
}
void StopInt(void)  interrupt 2	 //停止按键通过外部中断1
{
  TR0=0;
}