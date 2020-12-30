#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//LED端口定义
#define LED_RED PCout(0)	
#define LED_YELLOW PCout(1)	
#define LED_GREEN PCout(2)	
#define BEEP PAout(11)		
#define SB PCout(3)	
void LED_Init(void);	//初始化		 				    
#endif

















