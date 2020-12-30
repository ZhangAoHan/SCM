#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define JDQ PBout(5)	

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM7_Int_Init(u16 arr,u16 psc);
void LED_Init(void);
#endif


