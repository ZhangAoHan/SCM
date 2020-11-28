#ifndef __LED_H
#define __LED_H
#include "sys.h"

//通过改变TIM1->CCR1的值来改变占空比，从而控制LED0的亮度
#define LED0_PWM_VAL TIM1->CCR1     
 
void TIM1_PWM_Init(u16 arr,u16 psc);
#endif




