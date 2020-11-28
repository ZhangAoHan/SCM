/*****************************************************************************************
*文件名称：serial.h
*说明：本文件为串口通信驱动函数头文件
*功能：1.端口定义
       2.驱动函数声明
*修改：无
*版本：V1.0.0
*作者：YuanDong
*时间：2009.07.03
*****************************************************************************************/
#ifndef  _SERIAL_H_
#define  _SERIAL_H_ 1
#include "Include.h"
   #ifndef  SERIAL_GLOBAL
     #define SERIAL_EXT extern 
   #else
     #define SERIAL_EXT
   #endif   
   SERIAL_EXT void  serial_Init(void);                   //串口初始化
   SERIAL_EXT void  serial_PutChar(uchar sendChar);      //串口发送一个字符
   SERIAL_EXT void  serial_PutStr(uchar *str,uchar len); //串口发送一行字符串
   SERIAL_EXT uchar serial_GetChar(void);                //串口接收一个字符
#endif
