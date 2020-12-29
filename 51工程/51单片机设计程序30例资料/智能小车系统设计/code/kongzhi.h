/*******************************************************************************
* 文件名称：kongzhi.h                          
* 说明：本文件为驱动头文件小车控制驱动函数
* 功能：1.传感器端口定义 
        2.kongzhi.c中用到的函数说明
* 修改： 无
* 版本：1.0.0
* 作者：YuanDong 
* 时间：2009.7.14 
*******************************************************************************/

#ifndef kongzhi_H
#define kongzhi_H 1

  #ifndef kongzhi_GLOBAL
    #define kongzhi_EXT  extern
  #else 
    #define kongzhi_EXT 
  #endif
   	
  #define    uchar unsigned char
  #define    uint  unsigned int	
  			
  sfr	     WDT_CONTR = 0xe1;	         //定义看门狗地址
  #define    zhang_ai  P3_2
  #define	 stop_1	P1_5   	             //目标站点1
  #define	 stop_2	P1_6	             //目标站点2
  #define	 stop_3	P1_7	             //目标站点3	 
  #define    timer_data  (256 - 200)     //定时器预置值，12M时钟时，定时0.2ms
  #define	 spy		P0               //红外寻迹检测接口				 
  #define    key     P2   		        					 
  #define    PWM_T   100			      //定义PWM的周期T为10ms
  sbit	     PWM  = P1^0;				  //PWM波形输出	
  sbit	     DR   = P1^1;				      //方向控制	
  sbit	     ENA  = P1^2;				  //PWM波输出使能控制
  sbit       PWM2 = P1^3;				  //PWM2波形输出 
  sbit	     DR2  = P1^4;				  //方向2控制
  
  kongzhi_EXT  void	bizhang();
  kongzhi_EXT  void  stop();
  kongzhi_EXT  void  xunji();  
  kongzhi_EXT  void  timer_init();
  kongzhi_EXT  void delay();
  kongzhi_EXT  void jieshou();
  kongzhi_EXT  uchar dulie();
  kongzhi_EXT  uchar key_board();
  kongzhi_EXT  void keyboard();

#endif