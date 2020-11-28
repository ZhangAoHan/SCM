#include "led.h"

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{   	 
	RCC->APB2ENR|=1<<2;    //使能PORTa时钟	 
	GPIOA->CRL&=0XFF0000FF;
	GPIOA->CRL|=0X00333300;//PA.5推挽输出
	GPIOA->ODR|=1<<2;      //PA.5输出高 
	GPIOA->ODR|=1<<3;      //PA.5输出高
	GPIOA->ODR|=1<<4;      //PA.5输出高
	GPIOA->ODR|=1<<5;      //PA.5输出高
}






