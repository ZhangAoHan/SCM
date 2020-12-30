#include "timer.h"
#include "led.h"
#include "motor_control.h"
#include "lcd.h"
#include "as608_control.h"
extern u8 use_start;  
extern u16 t1,t2,t3,t4;     //计时
extern u8 use1,use2,use3,use4;   
extern	u8 temperature;  	    
extern u8 humidity;
	extern u16 adcx;    //tr
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟		  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占1，子优先级3，组2									 
}

void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
		date_read();           //每隔一秒读取一次环境温湿度数据  并控制灯的开关
		if(use1==1)
		{
			t1++;
		}

		if(use2==1)
		{
			t2++;
		}

		if(use3==1)
		{
			t3++;
		}

		if(use4==1)
		{
			t4++;
		}
		if(adcx>2500)
		{
			JDQ=0;
		}
		else
		{
			JDQ=1;
		}
	
	use_touch_scan();	//每秒检测一次 启动按键	
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}




extern vu16 USART2_RX_STA;
//定时器7中断服务程序		    
void TIM7_IRQHandler(void)
{ 	    		    
	if(TIM7->SR&0X01)//是更新中断
	{	 			   
		USART2_RX_STA|=1<<15;	//标记接收完成
		TIM7->SR&=~(1<<0);		//清除中断标志位		   
		TIM7->CR1&=~(1<<0);		//关闭定时器7	  
	}	      											 
} 
//基本定时器7中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器7!
void TIM7_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<5;//TIM7时钟使能    
 	TIM7->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM7->PSC=psc;  	//预分频器  
	TIM7->DIER|=1<<0;   //允许更新中断	 
	TIM7->CR1|=0x01;    //使能定时器7
  	MY_NVIC_Init(0,1,TIM7_IRQn,2);//抢占0，子优先级1，组2									 
}



#include "led.h"

void LED_Init(void)
{
	RCC->APB2ENR|=1<<3;    //使能PORTa时钟	   	   	 
	GPIOB->CRL&=0XFF0FFFFF; 
	GPIOB->CRL|=0X00300000;   	 
	GPIOB->ODR|=1<<5;      //PB.5 输出高								
}





















