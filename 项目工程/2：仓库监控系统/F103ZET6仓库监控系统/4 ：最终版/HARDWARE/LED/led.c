#include "led.h"

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{   	 
	RCC->APB2ENR|=1<<2;    //ʹ��PORTaʱ��	 
	GPIOA->CRL&=0XFF0000FF;
	GPIOA->CRL|=0X00333300;//PA.5�������
	GPIOA->ODR|=1<<2;      //PA.5����� 
	GPIOA->ODR|=1<<3;      //PA.5�����
	GPIOA->ODR|=1<<4;      //PA.5�����
	GPIOA->ODR|=1<<5;      //PA.5�����
}






