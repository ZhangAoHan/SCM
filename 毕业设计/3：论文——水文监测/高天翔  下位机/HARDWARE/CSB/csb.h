#ifndef __CSB_H
#define __CSB_H
#include <sys.h>	 
void TIM3_Cap_Init(u16 arr,u16 psc);
void Read_Distane(void);
void TIM3_IRQHandler(void);
extern u32 Distance;  
#endif
