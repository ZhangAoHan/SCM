#include "key.h"
#include "delay.h"

//������ʼ������
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTcʱ��  
	GPIOC->CRL&=0XFFFFFFF0;		  
	GPIOC->CRL|=0X00000008; 				   
 
} 

