#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define PWM TIM4->CCR3
void TIM3_Int_Init(u16 arr,u16 psc);
void DJ_PWM_Init(u16 arr,u16 psc);
#endif



