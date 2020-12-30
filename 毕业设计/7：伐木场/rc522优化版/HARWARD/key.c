#include "key.h"
#include "delay.h"

//按键初始化函数
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<7;     //使能PORTE时钟
	GPIOF->CRL&=0X00000000;	//PE2~4设置成输入	  
	GPIOF->CRL|=0X88888888; 				   
	GPIOF->ODR|=7<<2;	   	//PE2~4 上拉
} 