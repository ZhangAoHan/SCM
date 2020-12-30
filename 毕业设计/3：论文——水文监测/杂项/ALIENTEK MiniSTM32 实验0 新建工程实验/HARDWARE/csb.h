#ifndef __CSB_H
#define __CSB_H
#include <sys.h>	

extern u8 x;
void TIM2_Cap_Init(u16 arr,u16 psc);
void Read_Distane(void);
void TIM2_IRQHandler(void);


#endif
