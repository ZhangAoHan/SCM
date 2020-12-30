#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 

#define PWMA   TIM1->CCR1  //PA8
#define PWM TIM4->CCR3

#define AIN2   PFout(0)   //”“¬÷
#define AIN1   PFout(1)
void PWM_Init(u16 arr,u16 psc);  
void TIM3_PWM_Init(u16 arr,u16 psc);
void Motor_Init(void);
void DJ_PWM_Init(u16 arr,u16 psc);
#endif


