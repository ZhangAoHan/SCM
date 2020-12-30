#include "motor.h"
#include "delay.h"

void Motor_Init(void)
{
	RCC->APB2ENR|=1<<7;    //使能PORTa时钟	 
	GPIOF->CRL&=0XFFFFFF00;
	GPIOF->CRL|=0X00000022;//PA.5推挽输出
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
void DJ_PWM_Init(u16 arr,u16 psc)
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







