#include "Include.h"
#ifndef KEY_H
    #define KEY_H 1

    #ifndef KEY_GLOBAL
        #define KEY_EXT  extern
    #else
        #define KEY_EXT
    #endif

    #define READ_KEY(x,name,b)       ((x)?(b|=name):(b&=~name) )
//--------------------------------用户设置区------------------------------------------

    #define CAN_MORE_PRESS  0           // 是否允许多键都按: 允许为1;不允许为0 
    #define CAN_REPEAT      0           //是否允许重复按键: 允许为1;不允许为0 
    #define REPEAT_MODE     1           //重复模式: 先长后短为1;相同间隔为0 
    #define FIRST_TIMES     200         //重复按下时,第一次间隔时间 
    #define OTHER_TIMES     25          //第二次后间隔时间(如果重复模式为0时此值无效) 
    #define KEY_DELAY_TIME  20          //键盘扫描时间间隔　XXXus 
	#define KEY_FORCE_VALUE 0           //键盘有效电平，1为高电平，0为低电平 

	#define IN_PRESS_ONE      P1_0   //1号选手按键端口 
    #define IN_PRESS_TWO      P1_1   //2号选手按键端口 
    #define IN_PRESS_THREE    P1_2   //3号选手按键端口 
    #define IN_PRESS_FOUR     P1_3	 //4号选手按键端口 
	#define IN_PRESS_FIVE     P1_4   //5号选手按键端口 
    #define IN_PRESS_SIX      P1_5   //6号选手按键端口 
    #define IN_PRESS_SEVEN    P1_6   //7号选手按键端口 
    #define IN_PRESS_EIGHT    P1_7	 //8号选手按键端口 

/* 键盘重映射  注：当前结构下最大按键数为:8; 以2进制中的相应位来标识 */	   
	enum  KEY_VALUE{KEY_ONE = 0x01,KEY_TWO= 0x02, KEY_THREE = 0x04, KEY_FOUR = 0x08,KEY_FIVE=0x10,KEY_SIX=0x20,KEY_SEVEN=0x40,KEY_EIGHT=0x80,KEY_NULL = 0x00};
//------------------------------------------------------------------------------------
    KEY_EXT void    init_key(void);
    KEY_EXT uchar   get_key_value(void);
	KEY_EXT void delay_us(uint us);
	KEY_EXT void delay(uint us);
#endif
