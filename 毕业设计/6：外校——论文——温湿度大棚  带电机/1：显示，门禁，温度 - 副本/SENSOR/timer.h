#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define PWM TIM4->CCR3
void PWM_Init(u16 arr,u16 psc);
void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_Int(u16 arr);

#endif

