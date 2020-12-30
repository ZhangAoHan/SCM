#ifndef __TIMER_H
#define __TIMER_H	 
#include "sys.h"



void TIM3_Int_Init(u16 arr,u16 psc);
double avergearray(int* arr, int number);
void PH_read(u8 t);
void date_read(void);
void Rc522_read(void);
#endif
