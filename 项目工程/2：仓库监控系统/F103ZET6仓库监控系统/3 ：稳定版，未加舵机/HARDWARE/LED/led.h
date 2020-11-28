#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//LED端口定义
#define JDQ1 PAout(2)	// DS0   //控制继电器  低电平触发
#define JDQ2 PAout(3)	// DS1	
#define JDQ3 PAout(4)	// DS1
#define JDQ4 PAout(5)	// DS1

void LED_Init(void);	//初始化		 				    
#endif

















