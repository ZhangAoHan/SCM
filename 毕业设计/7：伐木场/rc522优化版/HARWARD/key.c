#include "key.h"
#include "delay.h"

//������ʼ������
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<7;     //ʹ��PORTEʱ��
	GPIOF->CRL&=0X00000000;	//PE2~4���ó�����	  
	GPIOF->CRL|=0X88888888; 				   
	GPIOF->ODR|=7<<2;	   	//PE2~4 ����
} 