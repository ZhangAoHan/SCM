#include "timer.h"
#include "sys.h" //因为设置中断优先级需要调用sys.c中的函数

void PWM_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟
	RCC->APB1ENR|=1<<2;	//TIM4时钟使能    
	GPIOB->CRH&=0XFFFFFFF0;	//PB8清除之前的设置
	GPIOB->CRH|=0X0000000B;	//复用功能输出
	TIM4->ARR=arr;             //设定计数器自动重装值 
	TIM4->PSC=psc;             //预分频器分频
	TIM4->CCMR2|=6<<4;         //CH3 PWM1模式		 
	TIM4->CCMR2|=1<<3;         //CH3预装载使能	    
	TIM4->CCER|=1<<8;          //CH3输出使能	
	TIM4->CR1=0x0080;          //ARPE使能 
	TIM4->CR1|=0x01;          //使能定时器3	
}
