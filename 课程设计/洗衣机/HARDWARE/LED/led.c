#include "led.h"


void LED_Init(void)
{
 
RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��	
GPIOB->CRH&=0XFFFFFF00; 
GPIOB->CRH|=0XFFFFFF33;//PB8,9 �������   	 
GPIOB->ODR|=0X00000300;      //P8,9 �����
	
}
 
