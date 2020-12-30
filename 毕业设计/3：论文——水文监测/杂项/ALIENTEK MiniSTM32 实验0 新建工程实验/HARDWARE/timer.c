#include "timer.h"
#include "csb.h"   
#include "led.h"
#include "rc522.h"

extern u8 times;
u8 time;
extern u8 tmp_buf[33];
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
	
	
			times++;
		if(times==1||times==2)
		{
			LED_RED=1;
			LED_YELLOW=0;
			LED_GREEN=0;
		}
		else if(times==3||times==4)
		{
			LED_RED=0;
			LED_YELLOW=1;
			LED_GREEN=0;
		}
				else if(times==5||times==6)
		{
			LED_RED=0;
			LED_YELLOW=0;
			LED_GREEN=1;
			if(times==6)
			{
				times=0;
			}
		}
		

	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}


