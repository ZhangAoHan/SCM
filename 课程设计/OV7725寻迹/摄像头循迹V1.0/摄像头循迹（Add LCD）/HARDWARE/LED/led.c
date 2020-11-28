#include "led.h"
		    
//LED IO初始化
void LED_Init(void)
{
 	RCC->APB2ENR|=1<<2;    //使能PORTA时钟	   	 
	RCC->APB2ENR|=1<<5;    //使能PORTD时钟	
	   	 
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003;//PA8 推挽输出   	 
    GPIOA->ODR|=1<<8;      //PA8 输出高
											  
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2推挽输出
	GPIOD->ODR|=1<<2;      //PD.2输出高 						 //PB.5 输出高

}
 
