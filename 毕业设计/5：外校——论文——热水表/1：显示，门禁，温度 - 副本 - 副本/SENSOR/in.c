#include "in.h"
#include "delay.h"

//������ʼ������
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTcʱ��  
	GPIOC->CRL&=0XFFFF0000;		  
	GPIOC->CRL|=0X00008888; 				   
	GPIOC->ODR|=8<<0;	 
} 




















