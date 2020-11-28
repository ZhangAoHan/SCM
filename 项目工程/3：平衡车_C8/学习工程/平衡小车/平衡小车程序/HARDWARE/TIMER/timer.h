#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#define TIM1_oc1_pwm TIM1->CCR1  //PA6  ◊Û
#define TIM1_oc2_pwm TIM1->CCR2    //PA7  ”“
void Timer_init(u16 arr,u16 psc);
void TIM2_init(u16 arr);
void TIM4_init(u16 arr);
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);
int Read_val(u8 TIMX);
#endif



