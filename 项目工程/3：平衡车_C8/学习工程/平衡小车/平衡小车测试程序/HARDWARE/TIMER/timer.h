#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#define TIM3_oc1_pwm TIM3->CCR1   //PA6
#define TIM3_oc2_pwm TIM3->CCR2    //PA7
//#define TIM3_oc3_pwm TIM3->CCR3     //PB0
//#define TIM3_oc4_pwm TIM3->CCR4   //PB1
void Timer_init(u16 arr,u16 psc);
//#define pwm1 PAout(6)
//#define pwm2 PAout(7)
//#define pwm3 PBout(0)
//#define pwm4 PBout(1)
void MOTO_PWM_init(void);
#endif



