#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY_mode  PAin(4)// PB3
#define KEY_train PAin(5)// PB4
#define FDC2214_reset PAin(6)// PB4
#define KEY_PRESSED 0

void KEY_Init(void);
u8 KEY_Scan(void);
void Sort_chooes(float *arr);

		 				    
#endif