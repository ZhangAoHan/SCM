#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define PWM TIM4->CCR3

void PWM_Init(u16 arr,u16 psc);


#endif

