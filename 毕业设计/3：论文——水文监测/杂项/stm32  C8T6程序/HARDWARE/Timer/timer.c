#include "timer.h"
#include "csb.h"   
#include "oled.h"
#include "led.h"

extern u8 times;
u8 time;
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM3->DIER|=1<<0;   //��������ж�	  
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2									 
}

//��ʱ��2�жϷ������  
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
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
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}


