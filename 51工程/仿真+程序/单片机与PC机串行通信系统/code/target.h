/****************************************************************************************
* 文件名称：Target.h
* 说明：本文件为串口头文件
* 功能：串口使用的函数说明
* 修改：无
* 版本：1.0.0
* 作者：YuanDong
* 时间：2009.5.30
*****************************************************************************************/
#ifndef TARGET_H
#define TARGET_H
#include "Include.h"
#ifndef TARGET_GLOBAL
     #define TARGET_EXT extern
#else
    #define TARGET_EXT
#endif
TARGET_EXT void  usart0_initial(void);             //使用定时器1,其初始化在usart0初始化中
TARGET_EXT void  send_char(uchar txd);           //串口发送一个字符
TARGET_EXT uchar get_char(void);                 //串口接收一个字符
TARGET_EXT void  send_str(uchar *str,uchar len);    //串口发送一行字符串
#endif
