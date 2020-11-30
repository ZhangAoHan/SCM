#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define JDQ1 PFout(0)	// DS0   //���Ƽ̵���  �͵�ƽ����
#define JDQ2 PFout(1)	// DS1	
#define KEY_UP  PAin(12)   	//PC5
#define KEY_DOWN  PAin(11)	 	//PA15 
#define KEY_TOUCH  PAin(4)	 	//PA15
void LED_Init(void);
void Key_init(void);
#endif




