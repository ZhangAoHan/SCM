#include "led.h"

void LED_Init(void)
{
	RCC->APB2ENR|=1<<4;    //ʹ��PORTaʱ��	   	 
	  RCC->APB2ENR|=1<<2;  	 
	GPIOC->CRL&=0XFFF00000; 
	GPIOC->CRL|=0X00033333;   	 
    GPIOC->ODR|=1<<0;      //PB.5 �����
	GPIOC->ODR|=1<<1;      //PB.5 �����
	GPIOC->ODR|=1<<2;      //PB.5 �����
	GPIOC->ODR|=1<<3;      //PB.5 �����
	GPIOA->CRH&=0XFFF00FFF; 
	GPIOA->CRH|=0X00033000;   	 
    GPIOA->ODR|=1<<11;      //PB.5 �����
//	GPIOA->ODR|=1<<12;      //PB.5 �����
											
}

