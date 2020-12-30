#include "in.h"
#include "delay.h"

//按键初始化函数
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<4;     //使能PORTc时钟  
	GPIOC->CRL&=0XFFFF0000;		  
	GPIOC->CRL|=0X00008888; 				   
	GPIOC->ODR|=8<<0;	 
} 




















