#ifndef __CONTROL_H
#define __CONTROL_H
#include <sys.h>	 
#include "lcd.h"
#include "text.h"	 
#include "csb.h"   
#include "delay.h"	

extern u32 Distance;  
extern float m1,m2;
void TFT_Display(void);
void TFT_S_Display(void);
void Clear_ss(u8 x,u16 y,u8 x1,u16 y1);
#endif


