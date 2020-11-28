#include "timer.h"
#include "usart.h" 
extern u8 key;
//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)  //控制LED量灭，表示程序正在运行
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟		  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占1，子优先级3，组2									 
}
//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)  //输出PWM控制LED亮的程度    本程序没用
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

u8 ov_frame; 	//统计帧数
//定时器6中断服务程序	 
void TIM6_IRQHandler(void)
{ 		    		  			    
	if(TIM6->SR&0X0001)//溢出中断
	{				    
//		printf("frame:%dfps\r\n",ov_frame);	//打印帧率
		ov_frame=0;	
		key++;	
	if(key>=4) key=0;		
	}				   
	TIM6->SR&=~(1<<0);//清除中断标志位 	    
}
//基本定时器6中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM6_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<4;//TIM6时钟使能    
 	TIM6->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM6->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟	  
	TIM6->DIER|=1<<0;   //允许更新中断	 
	TIM6->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM6_IRQn,2);//抢占1，子优先级3，组2									 
}















