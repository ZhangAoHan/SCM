#include "led.h"
		    
//LED IO��ʼ��
void LED_Init(void)
{
 	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��	   	 
	RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��	
	   	 
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003;//PA8 �������   	 
    GPIOA->ODR|=1<<8;      //PA8 �����
											  
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2�������
	GPIOD->ODR|=1<<2;      //PD.2����� 						 //PB.5 �����

}
 
