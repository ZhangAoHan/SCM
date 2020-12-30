#include "control.h"
#include "display.h"
#include "date.h"
#include "touch.h"  
#include "lcd.h"
#include "delay.h"	
extern u8 page;
extern u8 temperature;  	    
extern u8 humidity;  	
extern u8 temperature2;  	    
extern u8 humidity2;  
u8 set=0;
u8 i;
extern u8 settle;

void Io_In_Out(void)
{
	RCC->APB2ENR|=1<<4; 
	GPIOC->CRL&=0XFFF00000; 
	GPIOC->CRL|=0X00033333;   	 
    GPIOC->ODR|=0<<0;   
	GPIOC->ODR|=1<<1;  
    GPIOC->ODR|=0<<2;   
	GPIOC->ODR|=0<<3;  
	GPIOC->ODR|=1<<4;  
}

void use_control(void)
{
 if(page==0)
{

	if(set==0)
	{
		LCD_Clear(WHITE);
		delay_ms(100);
		Use1_init_diaplsy();
		set=1;
	}
	else
	{
		Use1_date_display();
	}
		use_touch();
	
}
if(page==1)
{
	if(set==0)
	{
		LCD_Clear(WHITE);
		delay_ms(100);
		date_init_display(0);
		set=1;
	}
	else 
	{
		date_display(0);
	}
	use_touch();
}
if(page==2)
{
	if(set==0)
	{
		LCD_Clear(WHITE);
		delay_ms(100);
		date_init_display(1);
		set=1;
	}
	else 
	{
		date_display(1);
	}
		use_touch();
}
if(page==3)
{
	if(set==0)
	{
		LCD_Clear(WHITE);
		delay_ms(100);
		Block_init_display();
		set=1;
	}
		use_touch();
}
}
void use_touch(void)
{
		tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(page==0)
			{
				if(tp_dev.x[0]>6&&tp_dev.x[0]<126&&tp_dev.y[0]>290&&tp_dev.y[0]<320)
				{
					settle=!settle;
				}
				if(tp_dev.x[0]>6&&tp_dev.x[0]<126&&tp_dev.y[0]>260&&tp_dev.y[0]<285)
				{
					page=1;
					set=0;
					LCD_Clear(WHITE);
					delay_ms(100);
				}
			}
			
			else if(page==1)
			{
				if(tp_dev.x[0]>30&&tp_dev.x[0]<130&&tp_dev.y[0]>245&&tp_dev.y[0]<270)
				{
					page=2;
					set=0;
					LCD_Clear(WHITE);
					delay_ms(100);
				}
				if(tp_dev.x[0]>180&&tp_dev.x[0]<230&&tp_dev.y[0]>245&&tp_dev.y[0]<270)
				{
					page=0;
					set=0;
					LCD_Clear(WHITE);
					delay_ms(100);
				}
			}
			
				else if(page==2)
			{
				if(tp_dev.x[0]>30&&tp_dev.x[0]<130&&tp_dev.y[0]>245&&tp_dev.y[0]<270)
				{
					page=1;
					set=0;
					LCD_Clear(WHITE);
					delay_ms(100);
				}
				if(tp_dev.x[0]>180&&tp_dev.x[0]<230&&tp_dev.y[0]>245&&tp_dev.y[0]<270)
				{
					page=0;
					set=0;
					LCD_Clear(WHITE);
					delay_ms(100);
				}
				if(tp_dev.x[0]>30&&tp_dev.x[0]<175&&tp_dev.y[0]>270&&tp_dev.y[0]<295)
				{
					page=3;
					set=0;
					LCD_Clear(WHITE);
					delay_ms(100);
				}
			}
				else if(page==3)
			{
				if(tp_dev.x[0]>190&&tp_dev.x[0]<240&&tp_dev.y[0]>295&&tp_dev.y[0]<320)
				{
					page=2;
					set=0;
					LCD_Clear(WHITE);
					delay_ms(100);
				}
			}
		}
	}
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

void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  	//预分频器7200,得到10Khz的计数时钟		  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占1，子优先级3，组2									 
}
//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
	DHT11_Read_Data(&temperature,&humidity);
	DHT12_Read_Data(&temperature2,&humidity2);
	date_save();
		if(page==3&&set==1)
		{
			LCD_Fill(50,80,150,145,WHITE);
			LCD_Fill(50,200,150,265,WHITE);
			Block_date_display();
		}
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}


