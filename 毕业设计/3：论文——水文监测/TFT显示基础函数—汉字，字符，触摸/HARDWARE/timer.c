#include "timer.h"
#include "sys.h" //因为设置中断优先级需要调用sys.c中的函数
#include "control.h"
#include "lcd.h"
extern u8 times;
extern u8 door;
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

//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
		
		if(door==1)
		{
			times++;
			if(times>5)
			{
			times=0;
			PWM=25; 	
			door=0;
			}		
		}
		else if(door==0)
		{
			use_touch_scan();
		}



	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟		  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占1，子优先级3，组2									 
}

void use_touch_scan(void)     // use_start=0  还没开始  use_start=1 开始  use_start=2  结束 
{
	if(KEY_UP==1&&door==0)
	{
		door=1;
		PWM=15;  
	}
}





















