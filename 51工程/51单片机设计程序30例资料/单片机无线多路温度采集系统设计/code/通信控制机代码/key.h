/***********************************************************************
*文件名称：key.h
*说明：本文件为键盘扫描驱动函数头文件
*功能：1.端口定义
       2.驱动函数声明
*修改：无
*版本：V1.0.0
*作者：YuanDong
*时间：2009.07.03
*************************************************************************/
#include "Include.h"
#ifndef KEY_H
    #define KEY_H 1
    #ifndef KEY_GLOBAL
        #define KEY_EXT  extern
    #else
        #define KEY_EXT
    #endif
    #define READ_KEY(x,name,b)       ((x) ? (b |= name):(b &= ~name) )
/*--------------------------------用户设置区------------------------------------------*/
    #define CAN_MORE_PRESS  0             // 是否允许多键都按: 允许为1;不允许为0 
    #define CAN_REPEAT      1              // 是否允许重复按键: 允许为1;不允许为0 
    #define REPEAT_MODE     1              // 重复模式: 先长后短为1;相同间隔为0 
    #define FIRST_TIMES     200              // 重复按下时,第一次间隔时间 
    #define OTHER_TIMES     25              // 第二次后间隔时间(如果重复模式为0时此值无效) 
    #define KEY_DELAY_TIME  20             // 键盘扫描时间间隔　XXXus 
 #define KEY_FORCE_VALUE 0              //键盘有效电平，1为高电平，0为低电平 
#define IN_PRESS_SECOND        P1_4     //秒设置键端口 
    #define IN_PRESS_MINUTE        P1_5     //分设置键端口 
    #define IN_PRESS_HOUR          P1_6     //时设置键端口 
    #define IN_PRESS_ALARM        P1_7	   //闹钟设置键端口 
    #define IN_PRESS_UP             P1_4     //秒设置键端口 
    #define IN_PRESS_DOWN         P1_5     //分设置键端口 
    #define IN_PRESS_START         P1_6      //时设置键端口 
    #define IN_PRESS_STOP       P1_7	//闹钟设置键端口  

    /* 键盘重映射  注：当前结构下最大按键数为:8; 以2进制中的相应位来标识*/
	enum  KEY_VALUE{KEY_UP = 0x01,KEY_DOWN  = 0x02, KEY_START = 0x04, KEY_STOP = 0x08,KEY_NULL = 0x00};
//------------------------------------------------------------------------------------
    KEY_EXT void    init_key(void);
    KEY_EXT uchar   get_key_value(void);
KEY_EXT void delay_us(uint us);
KEY_EXT void delay(uint us);
#endif
