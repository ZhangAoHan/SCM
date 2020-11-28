#ifndef REAL_TIMER_DS1302
#define REAL_TIMER_DS1302
#include "Include.h"
#ifndef CLOCK_GLOBAL
  #define CLOCK_EXT extern 
#else
  #define CLOCK_EXT
#endif
/***************************DS1302�ܽ�����****************************/
sbit clock_rst = P2^4;
sbit clock_io  = P2^3;       
sbit clock_sclk= P2^2;
/*********************Ϊ�˱�̷��㶨���λ����**********************/
sbit ACC0 = ACC ^ 0;
sbit ACC7 = ACC ^ 7;
#define second_address	0x80
#define minute_address	0x82
#define hour_address	0x84 
#define day_address	    0x86
#define month_address	0x88
#define year_address	0x8C
CLOCK_EXT void Clock_Write_Byte(uchar temp);//��ʱ��DS1302д��һ���ֽ�
CLOCK_EXT uchar Clock_Read_Byte(void);//��ʱ��DS1302��ȡһ���ֽ�
CLOCK_EXT void Clock_Write_Time(uchar address, uchar temp); //��ʱ��DS1302д��һ��ʱ��
CLOCK_EXT uchar Clock_Read_Time(uchar address);//��ʱ��DS1302����һ��ʱ��
CLOCK_EXT void Clock_Initial(uchar *clock_time );//ʱ�ӳ�ʼ��
CLOCK_EXT void Clock_Fresh(uchar * clock_time );//��ʱ��DS1302����ʱ��
#endif
