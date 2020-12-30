#include "io_control.h"

void Io_init(void)
{
	RCC->APB2ENR|=1<<2;    //ʹ��PORTaʱ��	   	 
	RCC->APB2ENR|=1<<3;    //ʹ��PORTaʱ��	 	
	GPIOA->CRH&=0X0FF00FFF; 
	GPIOA->CRH|=0X80088000;   	 
	GPIOA->ODR|=1<<12;      //PB.5 �����
	GPIOA->ODR|=1<<11;      //PB.5 �����
	GPIOA->ODR|=1<<15;      //PB.5 �����
	GPIOB->CRL&=0XFFFFFF00; 
	GPIOB->CRL|=0X00000033;   	 
	GPIOB->ODR|=0<<0;      //PB.5 �����
	GPIOB->ODR|=0<<1;      //PB.5 �����
}
