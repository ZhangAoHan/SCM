#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//LED端口定义
#define DHT11_JDQ PBout(5)	
#define TRSD_JDQ PBout(6)	
#define FS_JDQ PBout(7)	
#define BEEP_JDQ PBout(4)	
//#define LED_GREEN PAout(12)	
#define LED_RED PAout(9)	
#define LED_GREEN PAout(11)
void LED_Init(void);	//初始化		 				    
#endif








