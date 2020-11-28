#include "Motor.h"

void TIME3_PWM_init(u16 psc,u16 arr)   //使用定时器3同时输出4路PWM
{
	RCC->APB1ENR |=1<<1;     //使能定时器3
	TIM3->CR1 |=1<<0;        //使能计数器、定时器初始时钟为72M、计数器向上计数
	TIM3->CR1 |=1<<7;        //ARPE使能 
	TIM3->PSC =psc;        
	TIM3->ARR =arr;        
	TIM3->CCMR1 &=0X0000;   //通道1  2配置为输出
	TIM3->CCMR2 &=0X0000;   //通道3  4配置为输出
	TIM3->CCMR1 |=0X7878;   //通道1 2配置为PWM2模式 
	TIM3->CCMR2 |=0X7878;   //通道3 4配置为PWM2模式 
	TIM3->CCER |=0X3333;   //通道1 2 3 4  低电平有效     
}
void IO_init(void)
{
	RCC->APB2ENR |=0X000C;   //使能GPIOA B
	GPIOA->CRL &=0X00FFFFFF;  
	GPIOA->CRH &=0X0000FFFF; 
	GPIOA->CRL |=0XBB000000;  //定时器输出比较需要配置为复用推挽输出
	GPIOA->CRH |=0X33330000; 
	GPIOB->CRL &=0XFFFFFF00;  
	GPIOB->CRL |=0X000000BB;
}


