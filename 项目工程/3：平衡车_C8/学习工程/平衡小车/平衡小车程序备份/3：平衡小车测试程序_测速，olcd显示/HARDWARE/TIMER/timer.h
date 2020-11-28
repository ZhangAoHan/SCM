#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#define TIM3_oc1_pwm TIM3->CCR1   //PA6
#define TIM3_oc2_pwm TIM3->CCR2    //PA7
void Timer_init(u16 arr,u16 psc);
void MOTO_PWM_init(void);
void TIM2_init(u16 arr);
void TIM4_init(u16 arr);
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);
int Read_val(u8 TIMX);
#endif



