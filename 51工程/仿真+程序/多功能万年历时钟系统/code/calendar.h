/*******************************************************
*�ļ����ƣ�calendar
*�ļ����ܣ��洢���ڼ��㺯���������������ڣ����ڣ�������
������ת��
*���ߣ�yd
*ʱ�䣺09.06.20
********************************************************/
#ifndef CALENDAR_H
#define CALENDAR_H
#include "Include.h"
#include "lcd.h"
#ifndef CALENDAR_GLOBAL
  #define CALENDAR_EXT extern
#else
  #define CALENDAR_EXT
#endif
CALENDAR_EXT bit get_moon_day(uchar month_p,uint calendar_address);//��ȡ���ݱ���ũ���Ĵ��»�С�� ��������·���1, С�·���0
CALENDAR_EXT void Calendar_Convert( uchar c_flag, uchar * clock_time );//����BCD���������ݣ� ���BCD��������( 1901 - 2099 )
CALENDAR_EXT void Week_Convert( bit c, uchar * clock_time );//����BCD�������ݣ����BCD����

/**************************************************************************
* ����: void ershi( uchar * clock_time )
* ����: ����BCD���������ݣ� ���BCD��������( 2000 - 2099 )
* ��ڲ���:clock_time: ʱ�ӵ�ַ
* ���ڲ���: ��
*****************************************************************************/
CALENDAR_EXT void  Ershi( uchar * clock_time );//����BCD���������ݣ� ���BCD��������( 2000 - 2099 )
#endif