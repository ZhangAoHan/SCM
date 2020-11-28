#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "lcd.h"
#include "text.h"
   	

extern u8 flag;   					            //界面选择标准量
extern u8 cle; 					 	      	    //清屏标志量
extern uint32_t date2;
extern uint32_t fre2;
extern uint32_t fre2_last;
extern uint32_t result2;
extern uint32_t fre2_init_min,fre2_init_max;    //检测10000个数 找到最大值和最小值
extern uint32_t ch2_middle,ch2_wave;            //中值和波动区间
extern uint32_t by2,bb2,sy2,sb2,jy2,jb2;        //使系统具有存储功能
extern uint32_t y1,b1,y2,b2,y3,b3,y4,b4,y5,b5;  //使系统具有存储功能
extern u8 mode_selsct;                        //通道选择
extern u8 mode;                                 //数字选择

void FDC2214read(void);  
void Scan_sjb(void);
void C_control(void);
void S_control(void);
void C_Feedback(void);
void S_Feedback(void);
void Scan(u8 d);

#endif

