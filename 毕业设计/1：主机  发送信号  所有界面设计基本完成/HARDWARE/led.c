#include "led.h"
void LED_Init(void)
{   	 
//	RCC->APB2ENR|=1<<7;    //ʹ��PORTaʱ��	 
//	GPIOF->CRL&=0XFFFFFF00;
//	GPIOF->CRL|=0X00000033;//PA.5�������
//	GPIOF->ODR|=1<<0;      //PA.5�����
//	GPIOF->ODR|=1<<1;      //PA.5�����
}

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


