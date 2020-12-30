#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"


#define PWM TIM4->CCR3
#define PWM_VAL TIM1->CCR1  
void PWM_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
void PWM_Init(u16 arr,u16 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);
#endif



