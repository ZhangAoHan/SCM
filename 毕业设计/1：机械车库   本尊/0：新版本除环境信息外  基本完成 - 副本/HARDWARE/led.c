#include "led.h"

void Key_init(void)
{
	RCC->APB2ENR|=1<<2;    //ʹ��PORTaʱ��	
	GPIOA->CRH&=0XFFF00FFF; 
	GPIOA->CRH|=0X00088000;   	 
	GPIOA->ODR|=1<<12;      //PB.5 �����
	GPIOA->ODR|=1<<11;      //PB.5 �����
	GPIOA->CRL&=0XFFF0FFFF; 
	GPIOA->CRL|=0X00080000;   	 
	GPIOA->ODR|=1<<4;      //PB.5 �����
}




