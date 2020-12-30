#include "led.h"

void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTa时钟	   	 
	   	 
	GPIOA->CRH&=0XFFF00FF0; 
	GPIOA->CRH|=0X00033003;   	 
    GPIOA->ODR|=1<<8;      //PB.5 输出高
	GPIOA->ODR|=1<<11;      //PB.5 输出高
	GPIOA->ODR|=1<<12;      //PB.5 输出高
											
}

