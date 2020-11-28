#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "sys.h"
#include "lcd.h"
#include "text.h"
   	

extern u8 flag;   					//界面选择标准量
extern u8 cle; 					 	//清屏标志量
void C_display_init(void);   //猜拳界面初始化设计
void S_display_init(void);   //数字识别初始化设计
void cq_scan(u8 a);         //附加项  猜拳比大小初始化显示
#endif


