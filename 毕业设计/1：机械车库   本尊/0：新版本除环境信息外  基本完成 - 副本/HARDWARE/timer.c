#include "timer.h"
#include "led.h"
#include "motor_control.h"
#include "lcd.h"
#include "as608_control.h"
extern u8 use_start;  
extern u16 t1,t2,t3,t4;     //��ʱ
extern u8 use1,use2,use3,use4;   
extern	u8 temperature;  	    
extern u8 humidity;
	extern u16 adcx;    //tr
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM3->DIER|=1<<0;   //��������ж�	  
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2									 
}

void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
		date_read();           //ÿ��һ���ȡһ�λ�����ʪ������  �����ƵƵĿ���
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
	
	use_touch_scan();	//ÿ����һ�� ��������	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}




extern vu16 USART2_RX_STA;
//��ʱ��7�жϷ������		    
void TIM7_IRQHandler(void)
{ 	    		    
	if(TIM7->SR&0X01)//�Ǹ����ж�
	{	 			   
		USART2_RX_STA|=1<<15;	//��ǽ������
		TIM7->SR&=~(1<<0);		//����жϱ�־λ		   
		TIM7->CR1&=~(1<<0);		//�رն�ʱ��7	  
	}	      											 
} 
//������ʱ��7�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��7!
void TIM7_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<5;//TIM7ʱ��ʹ��    
 	TIM7->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
	TIM7->PSC=psc;  	//Ԥ��Ƶ��  
	TIM7->DIER|=1<<0;   //��������ж�	 
	TIM7->CR1|=0x01;    //ʹ�ܶ�ʱ��7
  	MY_NVIC_Init(0,1,TIM7_IRQn,2);//��ռ0�������ȼ�1����2									 
}



#include "led.h"

void LED_Init(void)
{
	RCC->APB2ENR|=1<<3;    //ʹ��PORTaʱ��	   	   	 
	GPIOB->CRL&=0XFF0FFFFF; 
	GPIOB->CRL|=0X00300000;   	 
	GPIOB->ODR|=1<<5;      //PB.5 �����								
}





















