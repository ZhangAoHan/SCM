/*****************************************************************************************
*文件名称：Include.h
*说明：系统主头文件
*功能：包含系统模块常用宏和头文件
*修改：无
*版本：V1.0.0
*作者：YuanDong
*时间：2009.07.03
*****************************************************************************************/
#ifndef _INCLUDE_H_
#define _INCLUDE_H_ 1
  #include <reg52.h>
  #include <intrins.h>
  #include <ABSACC.h>
  #define sei()  (EA = 1)
  #define cli()  (EA = 0)
  #define uchar unsigned char
  #define uint  unsigned int
  #define ulong unsigned long
#endif
