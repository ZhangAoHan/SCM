#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "lcd.h"
#include "control.h"

#define PWM TIM4->CCR3

void PWM_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
#endif

