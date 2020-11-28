#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "led.h"
//通过改变TIM3->CCR2的值来改变占空比，从而控制LED0的亮度
//#define DJ TIM3->CCR1   
////TIM1 CH1作为PWM DAC的输出通道 
//#define PWM_DAC_VAL  TIM1->CCR1 

//void TIM3_Int_Init(u16 arr,u16 psc);
//void TIM3_PWM_Init(u16 arr,u16 psc);
#define PWM TIM3->CCR1 

void PWM_Init(u16 arr,u16 psc);

//void TIM5_Cap_Init(u16 arr,u16 psc);
//void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM6_Int_Init(u16 arr,u16 psc);
#endif























