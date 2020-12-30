#include "motor.h"
#include "delay.h"
#include "usart.h"

void Motor_Init(void)
{
	RCC->APB2ENR|=1<<3;       //PORTB时钟使能   
	GPIOB->CRH&=0X00FFFFFF;   //PORTB12 13 14 15推挽输出
	GPIOB->CRH|=0X22000000;   //PORTB12 13 14 15推挽输出
}

void PWM_Init(u16 arr,u16 psc)
{		 					 
	Motor_Init();  //初始化电机控制所需IO
	RCC->APB2ENR|=1<<11; 	//TIM1时钟使能    
	GPIOA->CRH&=0XFFFFFFF0;	//PA8清除之前的设置
	GPIOA->CRH|=0X0000000B;	//复用功能输出 
	
	TIM1->ARR=arr;			//设定计数器自动重装值 
	TIM1->PSC=psc;			//预分频器设置
  
	TIM1->CCMR1|=7<<4;  	//CH1 PWM2模式		 
	TIM1->CCMR1|=1<<3; 		//CH1预装载使能	 
 	TIM1->CCER|=1<<0;   	//OC1 输出使能	   
	TIM1->BDTR|=1<<15;   	//MOE 主输出使能	   

	TIM1->CR1=0x0080;   	//ARPE使能 
	TIM1->CR1|=0x01;    	//使能定时器1 			
} 


