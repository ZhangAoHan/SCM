#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "led.h"
//ͨ���ı�TIM3->CCR2��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
//#define DJ TIM3->CCR1   
////TIM1 CH1��ΪPWM DAC�����ͨ�� 
//#define PWM_DAC_VAL  TIM1->CCR1 

//void TIM3_Int_Init(u16 arr,u16 psc);
//void TIM3_PWM_Init(u16 arr,u16 psc);
#define PWM TIM3->CCR1 

void PWM_Init(u16 arr,u16 psc);

//void TIM5_Cap_Init(u16 arr,u16 psc);
//void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM6_Int_Init(u16 arr,u16 psc);
#endif























