/****************************************************
*文件名称：sin.h
*文件功能：驱动DAC0832产生正弦波
*版本：0.0.1
*作者：yd
*时间：09.05.13
*****************************************************/
#ifndef SIN_H
#define SIN_H 1
  #include "Include.h"
  #ifndef SIN_GLOBAL
    #define SIN_EXT extern
  #else 
    #define SIN_EXT
  #endif
  SIN_EXT code uchar Sin[128];
//----------DAC0832数据端口映射------------
  #define  DAC0832       P1 
//------------------------------------------
  #define  SIN_FRE       100UL     //正弦波频率 HZ
  #define  SIN_SEG       64UL      //正弦波采样点数
  #define  SIN_SPACING   2         //产生正弦波时在SIn数组中取点间隔数
//---------------------------------------------
  SIN_EXT uchar timer0TH0;      //定时器0 TH0载入值寄存变量
  SIN_EXT uchar timer0TL0;      //定时器0 TL0载入值寄存变量
  SIN_EXT uchar sinCodeCount;	//Sin数组取数定位变量 
  SIN_EXT void timer0_init(double timer0Delay); //timer0初始化函数，单位为us
  SIN_EXT void dac0832_init(void);		        //0832初始化函数
  SIN_EXT void writeDAC0832(uchar dacDate);	    //0832数据写入函数
#endif