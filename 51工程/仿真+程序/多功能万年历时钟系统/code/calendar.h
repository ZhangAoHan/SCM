/*******************************************************
*文件名称：calendar
*文件功能：存储日期计算函数，包括计算星期，日期，和阳历
和阴历转换
*作者：yd
*时间：09.06.20
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
CALENDAR_EXT bit get_moon_day(uchar month_p,uint calendar_address);//读取数据表中农历的大月或小月 ，如果大月返回1, 小月返回0
CALENDAR_EXT void Calendar_Convert( uchar c_flag, uchar * clock_time );//输入BCD的阳历数据， 输出BCD阴历数据( 1901 - 2099 )
CALENDAR_EXT void Week_Convert( bit c, uchar * clock_time );//输入BCD阳历数据；输出BCD星期

/**************************************************************************
* 名称: void ershi( uchar * clock_time )
* 功能: 输入BCD的阳历数据， 输出BCD阴历数据( 2000 - 2099 )
* 入口参数:clock_time: 时钟地址
* 出口参数: 无
*****************************************************************************/
CALENDAR_EXT void  Ershi( uchar * clock_time );//输入BCD的阳历数据， 输出BCD阴历数据( 2000 - 2099 )
#endif