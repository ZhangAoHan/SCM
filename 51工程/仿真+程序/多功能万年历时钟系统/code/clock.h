#ifndef REAL_TIMER_DS1302
#define REAL_TIMER_DS1302
#include "Include.h"
#ifndef CLOCK_GLOBAL
  #define CLOCK_EXT extern 
#else
  #define CLOCK_EXT
#endif
/***************************DS1302管脚配置****************************/
sbit clock_rst = P2^4;
sbit clock_io  = P2^3;       
sbit clock_sclk= P2^2;
/*********************为了编程方便定义的位变量**********************/
sbit ACC0 = ACC ^ 0;
sbit ACC7 = ACC ^ 7;
#define second_address	0x80
#define minute_address	0x82
#define hour_address	0x84 
#define day_address	    0x86
#define month_address	0x88
#define year_address	0x8C
CLOCK_EXT void Clock_Write_Byte(uchar temp);//向时钟DS1302写入一个字节
CLOCK_EXT uchar Clock_Read_Byte(void);//从时钟DS1302读取一个字节
CLOCK_EXT void Clock_Write_Time(uchar address, uchar temp); //向时钟DS1302写入一个时间
CLOCK_EXT uchar Clock_Read_Time(uchar address);//从时钟DS1302读出一个时间
CLOCK_EXT void Clock_Initial(uchar *clock_time );//时钟初始化
CLOCK_EXT void Clock_Fresh(uchar * clock_time );//从时钟DS1302读出时间
#endif
