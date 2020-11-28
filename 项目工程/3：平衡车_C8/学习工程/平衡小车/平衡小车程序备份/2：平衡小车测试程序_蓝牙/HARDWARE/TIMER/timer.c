#include "timer.h"
#include "sys.h"

void Timer_init(u16 arr,u16 psc)
{
	RCC->APB1ENR |=1<<1;       //使能定时器3
	TIM3->CR1 |=1<<0;          //使能计数器、定时器初始时钟为72M、计数器向上计数
	TIM3->CR1 |=0X0080;
  	TIM3->PSC =psc;  
	TIM3->ARR =arr; 
	
	TIM3->CCMR1 |=7<<4;        //通道1配置
	TIM3->CCMR1 |=1<<3;
	TIM3->CCER  |=1<<0;        //通道1有效电平极性配置（TIM3->CCER=1：pwm为低电平有效，=3：pwm为高电平有效）
	
	TIM3->CCMR1 |=7<<12;       //通道2配置
	TIM3->CCMR1 |=1<<11;
	TIM3->CCER  |=1<<4;
	
	TIM3->CCMR2 |=7<<4;        //通道3配置
	TIM3->CCMR2 |=1<<3;
	TIM3->CCER  |=1<<8;
	
	TIM3->CCMR2 |=7<<12;       //通道4配置
	TIM3->CCMR2 |=1<<11;
	TIM3->CCER  |=1<<12;
}

void LED_init(void)
{
	
	RCC->APB2ENR|=1<<3;        //使能GPIOB
	GPIOB->CRL&=0XFFFFFF00;    //通道3 GPIOB0,复用推挽输出、输出速度50M
	GPIOB->CRL|=0X000000BB;    //通道4 GPIOB1,复用推挽输出、输出速度50M 
    GPIOB->ODR|=1<<0;          //设置GPIOB0为输出模式
	GPIOB->ODR|=1<<1;          //设置GPIOB0为输出模式
	
	RCC->APB2ENR|=1<<2;        //使能GPIOA
	GPIOA->CRL&=0X00FFFFFF;    //通道1 GPIOA6,复用推挽输出、输出速度50M
	GPIOA->CRL|=0XBB000000;    //通道2 GPIOA7,复用推挽输出、输出速度50M
	GPIOA->ODR|=1<<6;         //设置GPIOA6为输出模式
	GPIOA->ODR|=1<<7;         //设置GPIOA7为输出模式
}




