#include "csb.h"   
#include "delay.h"   
#include "usart.h" 
extern u32 Distance; 

void TIM2_Cap_Init(u16 arr,u16 psc)	
{	 
	RCC->APB1ENR|=1<<0;     //TIM2时钟使能     
	RCC->APB2ENR|=1<<2;    	//使能PORTa时钟   	 
	GPIOA->CRL&=0XFFFF00FF; 
	GPIOA->CRL|=0X00002800;//  	Pa 2  3 输入  输出
	
    TIM2->ARR=arr;  		//设定计数器自动重装值   
	TIM2->PSC=psc;  		//预分频器 
	TIM2->CCMR2|=1<<0;	//选择输入端 
 	TIM2->CCMR2|=0<<4; 	// 配置输入滤波器 不滤波
 	TIM2->CCMR2|=0<<2; 	//配置输入分频,不分频 

	TIM2->CCER|=0<<9; 	//上升沿捕获
	TIM2->CCER|=1<<8; 	//允许捕获计数器的值到捕获寄存器中

	TIM2->DIER|=1<<3;   //允许捕获中断				
	TIM2->DIER|=1<<0;   //允许更新中断	
	TIM2->CR1|=0x01;    //使能定时器2
	MY_NVIC_Init(1,3,TIM2_IRQn,1);
}
/**************************************************************************
函数功能：超声波接收回波函数
**************************************************************************/
u16 TIM2CH3_CAPTURE_STA,TIM2CH3_CAPTURE_VAL;
void Read_Distane(void)
{   
	 PAout(3)=1;
	 delay_us(15);  
	 PAout(3)=0;	
			if(TIM2CH3_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			Distance=TIM2CH3_CAPTURE_STA&0X3F;
			Distance*=65536;					        //溢出时间总和
			Distance+=TIM2CH3_CAPTURE_VAL;		//得到总的高电平时间
			Distance=Distance*170/1000;
		//	printf("%d \r\n",Distance);
			TIM2CH3_CAPTURE_STA=0;			//开启下一次捕获
		}				
}
/**************************************************************************
函数功能：超声波回波脉宽读取中断
**************************************************************************/
void TIM2_IRQHandler(void)
{ 		    		  			    
	u16 tsr;
	tsr=TIM2->SR;
	if((TIM2CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
				{
								if(tsr&0X01)//溢出
								{	    
										if(TIM2CH3_CAPTURE_STA&0X40)//已经捕获到高电平了
										{
											if((TIM2CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
											{
												TIM2CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
												TIM2CH3_CAPTURE_VAL=0XFFFF;
											}else TIM2CH3_CAPTURE_STA++;
										}	 
								}
						   	if(tsr&0x08)//捕获3发生捕获事件
				    	{	
											if(TIM2CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
											{	  			
											TIM2CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
											TIM2CH3_CAPTURE_VAL=TIM2->CCR3;	//获取当前的捕获值.
											TIM2->CCER&=~(1<<9);			//CC1P=0 设置为上升沿捕获
									  	}else  								//还未开始,第一次捕获上升沿
				   	{
											TIM2CH3_CAPTURE_STA=0;			//清空
											TIM2CH3_CAPTURE_VAL=0;
											TIM2CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
											TIM2->CNT=0;					//计数器清空
											TIM2->CCER|=1<<9; 				//CC1P=1 设置为下降沿捕获
							}		    
					    	}			     	    					   
		   }
			 TIM2->SR=0;//清除中断标志位 	     
}











