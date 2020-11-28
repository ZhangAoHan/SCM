/********************************************************
*实例名称：电子门铃
*实例功能：当按下门铃按钮时，产生500hz和750hz的方波来驱动
喇叭，产生两种不同频率的交替来产生两种声音
*作者：kxm
*时间：09.06.12
********************************************************/
#include "doorBell.h"
uchar t5hz;    //500hz频率计数
uchar t7hz;    //750hz频率计数
uint tcnt;     //定时器0中断计数
bit flag; 	   //500hz和750hz状态标示
void timer0_init(void)
{
   TMOD=0x02;  //定时器0工作在方式2,八位定时器自动载入
   TH0=0x06;   //12MHZ晶振,中断周期250*10^(-6)秒
   TL0=0x06; 
   ET0=1;	   //定时器0中断使能
   TR0=0;	   //定时器0默认状态停止运行
}
void int0_init(void)
{
  EX0 = 1;	 //外部中断0使能
  IT0 = 1;	 //外部中断0跳变中断
}
void main()
{
  timer0_init(); //定时器0初始化
  int0_init();	 //外部中断0初始化
  flag=0;
  t5hz=0x00;
  t7hz=0x00;
  tcnt=0x0000;
  sei();	    //开总中断
  while(1)
  {
    if(TR0==0)
      flag=0;  //门铃响过后转换成500hz状态
  }
}
void timer0_overflow(void) interrupt 1  //timer0溢出中断入口
{
  tcnt++; 
  if(tcnt==2000)                        //500hz和750hz方波各维持0.5s
  { 
    tcnt=0; 
    if(flag==0)  
      flag=~flag;  
    else   
      TR0=0;  
  } 
  if(flag==0)  //输出750hz方波
  { 
    t7hz++; 
    if(t7hz==3) 
    { 
      t7hz=0; 
      BELL_OUT=~BELL_OUT; 	//喇叭信号端口取反
    } 
  } 
  else        //输出500hz方波
  { 
    t5hz++; 
    if(t5hz==4) 
    { 
      t5hz=0; 
      BELL_OUT=~BELL_OUT; 
    } 
  } 
}
void int0(void)	interrupt 0	  //外部中断0中断入口，按键触发
{
  TR0=1;		             //开启定时器0,实现方波的输出
}