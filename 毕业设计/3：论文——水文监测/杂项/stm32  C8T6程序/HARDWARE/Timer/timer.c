#include "timer.h"
#include "csb.h"   
#include "oled.h"
#include "led.h"

extern u8 times;
u8 time;
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟		  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占1，子优先级3，组2									 
}

//定时器2中断服务程序  
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
	
//		Rc522_read();
			time++;
		if(time==1||time==2)
		{
			LED_RED=1;
			LED_YELLOW=0;
			LED_GREEN=0;
		}
		else if(time==3||time==4)
		{
			LED_RED=0;
			LED_YELLOW=1;
			LED_GREEN=0;
		}
				else if(time==5||time==6)
		{
			LED_RED=0;
			LED_YELLOW=0;
			LED_GREEN=1;
			if(time==6)
			{
				time=0;
			}
		}
		time=0;
		

	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}


