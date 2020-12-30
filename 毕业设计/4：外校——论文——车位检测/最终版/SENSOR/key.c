#include "key.h"
#include "delay.h"

//按键初始化函数
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<4;     //使能PORTc时钟  
	GPIOC->CRL&=0XFFFFFFF0;		  
	GPIOC->CRL|=0X00000008; 				   
 
} 

