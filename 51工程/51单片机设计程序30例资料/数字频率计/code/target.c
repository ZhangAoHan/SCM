#define TARGET_GLOBAL 1
#include "target.h"
uint  timer0Count;       //timer0溢出计数
uint  pulseCount;        //脉冲计数
uint  pulseCountTemp;    //脉冲计数寄存 
/*************************************************
*函数名称：timer0_init(void)
*函数功能：timer0初始化
*函数入口：无
*函数出口：无
*说明：本系统用12Mhz晶振,定时1ms
*************************************************/
void timer0_init(void)
{
  TMOD|=0x01;   //timer0工作在MODEL1,timer
  TH0=0xFC;
  TL0=0x18;
  ET0=1;        //timer0中断使能
  IP=0x02;      //timer0优先级最高
  TR0=1;		//timer0启动
}
/*************************************************
*函数名称：int0_init(void)
*函数功能：外部中断0初始化
*函数入口：无
*函数出口：无
*************************************************/
void int0_init(void) 
{
    EX0 = 1;	 //外部中断0使能
    IT0 = 1;	 //init0跳变中断
}
void target_init(void)
{
  timer0_init();
  int0_init();
  timer0Count=0;
  pulseCount=0;
  pulseCountTemp=0;
}
void T0_overflow(void) interrupt 1	//timer0溢出中断,定时1ms
{
  TH0=0xFC;
  TL0=0x18;
  cli();
  //IE0=0;
  if(timer0Count<1000)
    timer0Count++;
  else
  {
    
    pulseCountTemp=pulseCount-pulseCount/(uint)36;	//频率计数校准
	pulseCount=0;
    timer0Count=0;
  } 
  sei();
}
void int0(void) interrupt 0	//int0中断入口函数,实时计数检测频率
{
  pulseCount++;
}
/*********************************************
*函数名称：uint get_fre_number(void)
*函数功能：计算频率，1~1000HZ
*********************************************/
uint get_fre_number(void)
{
  return pulseCountTemp;
}