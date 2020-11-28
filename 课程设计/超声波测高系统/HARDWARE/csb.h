#ifndef __CSB_H
#define __CSB_H
#include <sys.h>	
#include "lcd.h"
#include "control.h"   
extern u8 x;
void TIM2_Cap_Init(u16 arr,u16 psc);
void Read_Distane(void);
void TIM2_IRQHandler(void);
void TIM3_Int_Init(u16 arr,u16 psc);

#endif
