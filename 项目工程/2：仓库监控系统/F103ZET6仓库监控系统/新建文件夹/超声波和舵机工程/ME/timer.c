#include "timer.h"
#include "sys.h" //因为设置中断优先级需要调用sys.c中的函数

void PWM_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
	GPIOA->CRL&=0XF0FFFFFF;	//PA6清除之前的设置
	GPIOA->CRL|=0X0B000000;	//复用功能输出
	TIM3->ARR=arr;             //设定计数器自动重装值 
	TIM3->PSC=psc;             //预分频器分频
	TIM3->CCMR1|=6<<4;         //CH1 PWM1模式		 
	TIM3->CCMR1|=1<<3;         //CH1预装载使能	    
	TIM3->CCER|=1<<0;          //CH1输出使能	
	TIM3->CR1=0x0080;          //ARPE使能 
	TIM3->CR1|=0x01;          //使能定时器3	
}

