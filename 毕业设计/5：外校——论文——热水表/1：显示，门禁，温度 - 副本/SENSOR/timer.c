#include "timer.h"
#include "sys.h" //因为设置中断优先级需要调用sys.c中的函数
#include "rc522.h"
#include "lcd.h"
#include "text.h"
#include "memory.h" 
#include "delay.h"	 
#include "led.h"
u8 t;
u8 nn=0;
extern u16 SL;
//定时器3中断服务程序	 
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//溢出中断
	{

		
		t++;
		if(nn==0)
		{
		SL=TIM3->CNT;
		TIM3->CNT=0;
		}

		if(t>=5)
		{
			t=0;	
			tempin_memory();
			tempout_memory();
		}

	}				   
	TIM2->SR&=~(1<<0);//清除中断标志位 	    
}
void TIM2_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;	//TIM3时钟使能    
 	TIM2->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM2->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟		  
	TIM2->DIER|=1<<0;   //允许更新中断	  
	TIM2->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM2_IRQn,2);//抢占1，子优先级3，组2									 
}



//通用定时器3 用作外部计数器 初始化
//arr：计数自动重装值。

	void TIM3_Int(u16 arr)

	{

	RCC->APB2ENR|=1<<5;//开启GPIOD端口时钟

	GPIOD->CRL &= 0xfffff0ff;

	GPIOD->CRL |= 0x00000400;//PD.2 浮空输入 



	RCC->APB1ENR |= 1<<1;//使能TIM3时钟



	TIM3->ARR=arr;  //设定计数器自动重装值

	TIM3->PSC=0; //不分频


	TIM3->SMCR &= ~(0xf<<8);//无滤波

	TIM3->SMCR &= ~(3<<12);//关闭预分频

	TIM3->SMCR |= 1<<15;//ETR被反相，低电平或下降沿有效

	TIM3->SMCR |= 1<<14;//使能外部时钟模式2



	TIM3->DIER |= 1<<0;//允许更新中断

	TIM3->DIER |= 1<<6;//允许触发中断



	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占1，子优先级3，组2 



	TIM3->CNT = 0x0;//清零计数器

	TIM3->CR1 |= 1<<0;//使能定时器，开启计数。

	}




//定时器3中断服务程序 ?

	void TIM3_IRQHandler(void)

	{ 

	if(TIM3->SR&0X0001)//溢出中断

	{
		TIM3->CNT = 65535;//清零计数器
	 
	} 
	TIM3->SR&=~(1<<0);//清除中断标志位 ?

	}



