#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//LED�˿ڶ���
#define LED_RED PBout(10)	
#define LED_YELLOW PBout(11)	
#define LED_GREEN PBout(12)	
#define YD  PAin(13)   	//PC5

void LED_Init(void);	//��ʼ��		 				    
#endif





