#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"


void TIM4_Config(uint16_t Period,uint16_t Prescaler,uint16_t Seize_priority,uint16_t Sub_priority);
void TIM3_Config(uint16_t Period,uint16_t Prescaler,uint16_t Seize_priority,uint16_t Sub_priority);

#endif