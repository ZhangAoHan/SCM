#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//LED端口定义
#define LED_RED PAout(8)	
#define LED_YELLOW PAout(11)	
#define LED_GREEN PAout(12)	

void LED_Init(void);	//初始化		 				    
#endif

















