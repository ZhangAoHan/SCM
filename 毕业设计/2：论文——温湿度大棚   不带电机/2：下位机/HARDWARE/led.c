#include "led.h"

void LED_Init(void)
{
	RCC->APB2ENR|=1<<3;    //ʹ��PORTaʱ��	   	 
	RCC->APB2ENR|=1<<2;    //ʹ��PORTaʱ��	   	 
	GPIOB->CRL&=0X0000FFFF; 
	GPIOB->CRL|=0X33330000;   	 
    GPIOB->ODR|=1<<7;      //PB.5 �����
	GPIOB->ODR|=1<<6;      //PB.5 �����
	GPIOB->ODR|=1<<5;      //PB.5 �����
	GPIOB->ODR|=1<<4;      //PB.5 �����
	
	GPIOA->CRH&=0XFFFF0F0F; 
	GPIOA->CRH|=0X00003030;   	 
    GPIOA->ODR|=0<<9;      //PB.5 �����
	GPIOA->ODR|=0<<11;      //PB.5 �����										
}

