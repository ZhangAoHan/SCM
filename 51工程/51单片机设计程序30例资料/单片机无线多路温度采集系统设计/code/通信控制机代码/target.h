/*****************************************************************************************
*文件名称：target.h
*说明：本文件为继电器和蜂鸣器驱动函数头文件
*功能：1.端口定义
       2.驱动函数声明
*修改：无
*版本：V1.0.0
*作者：YuanDong
*时间：2009.07.03
*****************************************************************************************/
#ifndef _TARGET_H_
#define _TARGET_H_ 1
#include "Include.h"
   #ifndef TARGET_GLOBAL
      #define TARGET_EXT extern
   #else
      #define TARGET_EXT
   #endif
   /*********继电器控制端口定义*********/
   sbit relayPort = P3^5;
   /*********蜂鸣器控制端口定义*********/
   sbit buzzerPort = P1^4;
   TARGET_EXT void relay_Init(void);
   TARGET_EXT void buzzer_Init(void);
   TARGET_EXT void relay_Command(bit status);
   TARGET_EXT void buzzer_Command(bit status);
#endif
