#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


#define KEY_UP  PAin(12)   	//PC5
#define KEY_DOWN  PAin(11)	 	//PA15 
#define KEY_TOUCH  PAin(4)	 	//PA15

void Key_init(void);
#endif


