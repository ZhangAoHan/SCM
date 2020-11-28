#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define PWM TIM3->CCR1 

void PWM_Init(u16 arr,u16 psc);


#endif

