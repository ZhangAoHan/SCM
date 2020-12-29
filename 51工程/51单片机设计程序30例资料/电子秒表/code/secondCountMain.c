/****************************************************
*ʵ�����ƣ����
*ʵ��˵������ʵ��ʵ��0.01S~59�ֵļ�ʱ������Start��ʱ
��ʼ����,��ʱ����Stop��ʱֹͣ��ʱ,����Clear��ʱ����
��ʾ����Start����Stop���ֱ�ͨ���ⲿ�ж�0���ⲿ�ж�1��
ʵ�ֲ���
*���ߣ�kxm
*ʱ�䣺09.06.13
****************************************************/
#include "target.h"
#include "led.h"
/*ʱ����ʾ������,��������Ϊ:�ָ�λ,�ֵ�λ;���λ,���λ;�����λ,�����λ*/
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
void T0_OverFlow(void) interrupt 1 //��ʱ��0����ж�,��ʱ10ms
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
void StartInt(void) interrupt 0	  //��������ͨ���ⲿ�ж�0
{
  TR0=1;
}
void StopInt(void)  interrupt 2	 //ֹͣ����ͨ���ⲿ�ж�1
{
  TR0=0;
}