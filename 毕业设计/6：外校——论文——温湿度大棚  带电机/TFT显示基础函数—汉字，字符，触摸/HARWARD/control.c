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
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
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
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��
	RCC->APB1ENR|=1<<2;	//TIM4ʱ��ʹ��    
	GPIOB->CRH&=0XFFFFFFF0;	//PB8���֮ǰ������
	GPIOB->CRH|=0X0000000B;	//���ù������
	TIM4->ARR=arr;             //�趨�������Զ���װֵ 
	TIM4->PSC=psc;             //Ԥ��Ƶ����Ƶ
	TIM4->CCMR2|=6<<4;         //CH3 PWM1ģʽ		 
	TIM4->CCMR2|=1<<3;         //CH3Ԥװ��ʹ��	    
	TIM4->CCER|=1<<8;          //CH3���ʹ��	
	TIM4->CR1=0x0080;          //ARPEʹ�� 
	TIM4->CR1|=0x01;          //ʹ�ܶ�ʱ��3	
}

void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM3->DIER|=1<<0;   //��������ж�	  
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2									 
}
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
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
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}


