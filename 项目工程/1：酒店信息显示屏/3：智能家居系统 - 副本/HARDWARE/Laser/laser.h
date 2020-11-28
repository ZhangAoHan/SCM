#ifndef __LASER_H
#define __LASER_H
#include "sys.h"

#define Light TIM1->CCR1  
#define Shock GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//»ðÑæ
#define Flame  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//Õñ¶¯
#define Beep PBout(13)	
void TIM1_PWM_Init(u16 arr,u16 psc);
void Light_init(void);
void BEEP_Init(void);
#endif


