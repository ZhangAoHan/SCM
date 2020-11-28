#include "timer.h"
#include "led.h"
#include "usart.h"
#include "ucos_ii.h"	//ucos 使用	 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/10
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//********************************************************************************
//V1.1 20150110
//1,增加TIM3_PWM_Init函数。
//2,增加LED0_PWM_VAL宏定义，控制TIM3_CH2脉宽		
//V1.2 20150110
//1,新增TIM5_Cap_Init函数
//2,新增TIM5_IRQHandler中断服务函数	 
//V1.3 20150115
//1,新增TIM1_PWM_Init函数
//V1.4 20150118
//1,增加TIM6_Int_Init函数。
//2,增加TIM6_IRQHandler函数
//V1.5 20150314
//1,增加TIM7_Int_Init函数。
//2,增加TIM7_IRQHandler函数
//////////////////////////////////////////////////////////////////////////////////  

vu8 frame_cnt; 
//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		   	    
	OSIntEnter();        
	if(TIM3->SR&0X0001)//溢出中断
	{
		if(frame_cnt)printf("frame:%d\r\n",frame_cnt);//打印帧率 
		frame_cnt=0;
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	 			    
	OSIntExit();  											 
}
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
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
void TIM3_PWM_Init(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<1; 	//TIM3时钟使能    
	RCC->APB2ENR|=1<<3;    	//使能PORTB时钟	
	GPIOB->CRL&=0XFF0FFFFF;	//PB5输出
	GPIOB->CRL|=0X00B00000;	//复用功能输出 	  	 
	   
	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
	AFIO->MAPR&=0XFFFFF3FF; //清除MAPR的[11:10]
	AFIO->MAPR|=1<<11;      //部分重映像,TIM3_CH2->PB5

	TIM3->ARR=arr;			//设定计数器自动重装值 
	TIM3->PSC=psc;			//预分频器不分频
	
	TIM3->CCMR1|=7<<12;  	//CH2 PWM2模式		 
	TIM3->CCMR1|=1<<11; 	//CH2预装载使能	   
	TIM3->CCER|=1<<4;   	//OC2 输出使能	   
	TIM3->CR1=0x0080;   	//ARPE使能 
	TIM3->CR1|=0x01;    	//使能定时器3 											  
}  	 
//定时器5通道1输入捕获配置
//arr：自动重装值
//psc：时钟预分频数
void TIM5_Cap_Init(u16 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<3;   	//TIM5 时钟使能 
	RCC->APB2ENR|=1<<2;    	//使能PORTA时钟  
	 
	GPIOA->CRL&=0XFFFFFFF0;	//PA0 清除之前设置  
	GPIOA->CRL|=0X00000008;	//PA0 输入   
	GPIOA->ODR|=0<<0;		//PA0 下拉
	  
 	TIM5->ARR=arr;  		//设定计数器自动重装值   
	TIM5->PSC=psc;  		//预分频器 

	TIM5->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
 	TIM5->CCMR1|=0<<4; 		//IC1F=0000 配置输入滤波器 不滤波
 	TIM5->CCMR1|=0<<10; 	//IC2PS=00 	配置输入分频,不分频 

	TIM5->CCER|=0<<1; 		//CC1P=0	上升沿捕获
	TIM5->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中

	TIM5->DIER|=1<<1;   	//允许捕获中断				
	TIM5->DIER|=1<<0;   	//允许更新中断	
	TIM5->CR1|=0x01;    	//使能定时器2
	MY_NVIC_Init(2,0,TIM5_IRQn,2);//抢占2，子优先级0，组2	   
}

//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到高电平;1,已经捕获到高电平了.
//[5:0]:捕获高电平后溢出的次数
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM5->SR;
 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(tsr&0X01)//溢出
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			    TIM5CH1_CAPTURE_VAL=TIM5->CCR1;	//获取当前的捕获值.
	 			TIM5->CCER&=~(1<<1);			//CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
	 			TIM5->CNT=0;					//计数器清空
	 			TIM5->CCER|=1<<1; 				//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
	TIM5->SR=0;//清除中断标志位 	    
}
//TIM1 CH1 PWM输出设置 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置  
	RCC->APB2ENR|=1<<2;   	//使能PORTA时钟	 
	RCC->APB2ENR|=1<<11;   	//使能TIM1时钟	
 	  	
	GPIOA->CRH&=0XFFFFFFF0;	//PA8输出
	GPIOA->CRH|=0X0000000B;	//复用功能输出 	  
 
	TIM1->ARR=arr;			//设定计数器自动重装值 
	TIM1->PSC=psc;			//预分频器分频设置
	
	TIM1->CCMR1|=7<<4;  	//CH1 PWM2模式		 
	TIM1->CCMR1|=1<<3; 		//CH1 预装载使能	   

	TIM1->CCER|=1<<1;   	//OC1 低电平有效 
	TIM1->CCER|=1<<0;   	//OC1 输出使能	
	TIM1->BDTR|=1<<15;   	//MOE 主输出使能,高级定时器必须开启这个  

	TIM1->CR1=0x0080;   	//ARPE使能 
	TIM1->CR1|=0x01;    	//使能定时器1											  
} 

extern void nes_vs10xx_feeddata(void);
//定时器6中断服务程序	 
void TIM6_IRQHandler(void)
{ 		    		  			    
	OSIntEnter();    
	if(TIM6->SR&0X0001)//溢出中断
	{				    
		nes_vs10xx_feeddata();//填充数据	  	   				     	    	
	}				   
	TIM6->SR&=~(1<<0);//清除中断标志位 	    
	OSIntExit();  											 
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
//LCD 背光PWM输出初始化
//初始化背光参数为:PWM控制频率为80Khz
//通过LCD_BLPWM_VAL设置LCD背光亮度.
//0,最暗;250,最暗.
void LCD_PWM_Init(void)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB2ENR|=1<<13; 	//TIM8时钟使能    
	RCC->APB2ENR|=1<<3;    	//使能PORTB时钟	 			 
	  	
	GPIOB->CRL&=0XFFFFFFF0;	//PB0输出
	GPIOB->CRL|=0X0000000B;	//复用功能输出 	  
	GPIOB->ODR|=1<<0;		//PB0上拉	 

	TIM8->ARR=100;			//设定计数器自动重装值为100.频率为100Hz 
	TIM8->PSC=7200-1;		//预分频器7200
	
	TIM8->CCMR1|=7<<12; 	//CH2 PWM2模式		 
	TIM8->CCMR1|=1<<11; 	//CH2预装载使能	   

	TIM8->CCER|=1<<6;   	//OC2互补输出使能	   
 	TIM8->CCER|=1<<7;   	//OC2N低电平有效	   
	TIM8->BDTR|=1<<15;   	//MOE主输出使能	   

	TIM8->CR1=0x0080;   	//ARPE使能 
	TIM8->CR1|=0x01;    	//使能定时器8 										  
} 
extern vu16 USART3_RX_STA;
//定时器7中断服务程序		    
void TIM7_IRQHandler(void)
{ 	
	OSIntEnter();    		    
	if(TIM7->SR&0X01)//是更新中断
	{	 			   
		USART3_RX_STA|=1<<15;	//标记接收完成
		TIM7->SR&=~(1<<0);		//清除中断标志位		   
		TIM7->CR1&=~(1<<0);		//关闭定时器7	  
	}	    
	OSIntExit();  											 
} 
//基本定时器7中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM7_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<5;//TIM7时钟使能    
 	TIM7->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM7->PSC=psc;  	//预分频器  
	TIM7->DIER|=1<<0;   //允许更新中断	 
	TIM7->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(0,1,TIM7_IRQn,2);//抢占0，子优先级1，组2									 
}














