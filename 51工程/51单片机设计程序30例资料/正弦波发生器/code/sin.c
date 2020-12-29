#define SIN_GLOBAL 1
#include "sin.h"
//正弦波128个采样点寄存数组 
code uchar Sin[128] = {
                        64,67,70,73,76,79,82,85,88,91,94,96,99,102,104,106,
						109,111,113,115,117,118,120,121,123,124,125,126,126,
						127,127,127,127,127,127,127,126,126,125,124,123,121,
						120,118,117,115,113,111,109,106,104,102,99,96,94,91,
						88,85,82,79,76,73,70,67,64,60,57,54,51,48,45,42,39,
						36,33,31,28,25,23,21,18,16,14,12,10,9,7,6,4,3,2,1,
						1,0,0,0,0,0,0,0,1,1,2,3,4,6,7,9,10,12,14,16,18,21,23,
						25,28,31,33,36,39,42,45,48,51,54,57,60
                      };
/**********************************************************
*函数名称：Timer0_init(double timer0Delay)
*函数功能：定时器0初始化
*函数入口：timer0Delay,定时器定时时间,单位为毫秒
*函数出口：无
**********************************************************/
void Timer0_init(double timer0Delay)
{
   double time;
   double timeTemp;
   timer0TH0=0x00;
   timer0TL0=0x00;
   timeTemp=0x00;
   time=(double)(((double)12)/((F_CPU)/1000000)); 
   if(((double)255)*time>timer0Delay)
    {
       timer0TH0=0x00;
	   timer0TL0=(uchar)(256ul-timer0Delay/time);
    }
   else
    {
	  while(timeTemp>timer0Delay)
	  {
	   timeTemp+=time;
	   timer0TH0++;  
	  }
	  timer0TH0--;				 
	  timeTemp=timeTemp-((double)timer0TH0)*time;
	  timer0TL0=(uchar)(256ul-timeTemp/time);
    }
   TMOD|=0x01;                               //GATE=0,TR=1运行;C/T=1,counter,0,timer;01十六进制 
   TH0=timer0TH0;
   TL0=timer0TL0;
   TR0=1;	                                 //timer0 控制位，为1时启动timer0
   ET0=1;                                    //timer0 中断使能
}
/**********************************************************
*函数名称：dac0832_init(void)	
*函数功能：D/A转换芯片dac0832初始化
*函数入口：无
*函数出口：无
**********************************************************/
void dac0832_init(void)	                    
{
  sinCodeCount=0;
  DAC0832=Sin[0]; 
}
/**********************************************************
*函数名称：writeDAC0832(uchar dacDate)	
*函数功能：向D/A转换芯片dac0832数据口写数据
*函数入口：dacDate
*函数出口：无
**********************************************************/
void writeDAC0832(uchar dacDate)            
{
  DAC0832=dacDate;
}
