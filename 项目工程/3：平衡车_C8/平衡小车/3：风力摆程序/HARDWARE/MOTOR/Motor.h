#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
#define Motor1 TIM3->CCR1     //A6
#define Motor2 TIM3->CCR2     //A7 
#define Motor3 TIM3->CCR3     //B0
#define Motor4 TIM3->CCR4     //B1
#define Motor1Vcc PAout(14)   
#define Motor1Gnd PAout(15)   
#define Motor2Vcc PAout(12)    
#define Motor2Gnd PAout(13)  
void TIME3_PWM_init(u16 psc,u16 arr);   //使用定时器3同时输出4路PWM
void IO_init(void);
#endif


