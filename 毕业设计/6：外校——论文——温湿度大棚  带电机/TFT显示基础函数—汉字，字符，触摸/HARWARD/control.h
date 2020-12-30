#ifndef __CONTROL_H
#define __CONTROL_H	
#include "sys.h"
				
#define FS PCout(1)
#define LED_YELLOW PCout(0)
#define LED_BLUE PCout(2)
#define LED_RED PCout(3)
#define BEEP PCout(4)

#define LED_PWM TIM4->CCR3

void TIM3_Int_Init(u16 arr,u16 psc);
	
void PWM_Init(u16 arr,u16 psc);
void use_control(void);
void Io_In_Out(void);
void use_touch(void);
#endif 












