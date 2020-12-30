#include "timer.h"
#include "sys.h" //因为设置中断优先级需要调用sys.c中的函数
#include "adc.h"
#include "dht11.h"
#include "led.h"
#include "control.h"

	extern u16 adcx;    //tr
	extern u16 adcx1;    //光敏
	extern u16 adcx2;    //MQ3
	extern	u8 temperature;  	    
	extern u8 humidity;
	extern u8 door;
	u8 i,di,si;
	extern u8 set;
	extern u8 settle;
//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
		i++;
//		adcx1=Get_Adc_Average(ADC_CH1,10);
//		adcx=Get_Adc_Average(ADC_CH2,10);	
//		adcx2=Get_Adc_Average(ADC_CH3,10);
//		DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值	
		Rc522_read();
		if(set==1)
		{
			si++;
			if(si==25)
			{
				set=0;
				si=0;
			}
		}
		if(i==50)
		{
			i=0;
			DHT11_JDQ=!DHT11_JDQ;
			TRSD_JDQ=!TRSD_JDQ;
			
	//FS_JDQ=!FS_JDQ
			settle=!settle;
		}
		if(door==1)
		{
			di++;
			PWM=10;    //开门5s
			if(di>=30)
			{
				di=0;
				door=0;
				PWM=20; 	
			}
		}
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
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

void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟		  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占1，子优先级3，组2									 
}
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


