#include "led.h"

void LED_Init(void)
{
	RCC->APB2ENR|=1<<3;    //使能PORTa时钟	   	 
	 RCC->APB2ENR|=1<<2;   	 
	GPIOA->CRH&=0XFF0FFFFF; 
	GPIOA->CRH|=0X00800000; 
	GPIOB->CRH&=0XFFF000FF; 
	GPIOB->CRH|=0X00033300;   	 
    GPIOB->ODR|=0<<10;      //PB.5 输出高
	GPIOB->ODR|=0<<11;      //PB.5 输出高
	GPIOB->ODR|=0<<12;      //PB.5 输出高

											
}
