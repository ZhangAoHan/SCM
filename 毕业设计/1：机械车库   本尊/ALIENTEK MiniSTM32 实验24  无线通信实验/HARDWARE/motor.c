#include "motor.h"
#include "delay.h"
#include "usart.h"

void Motor_Init(void)
{
	RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ��   
	GPIOB->CRH&=0X00FFFFFF;   //PORTB12 13 14 15�������
	GPIOB->CRH|=0X22000000;   //PORTB12 13 14 15�������
}

void PWM_Init(u16 arr,u16 psc)
{		 					 
	Motor_Init();  //��ʼ�������������IO
	RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��    
	GPIOA->CRH&=0XFFFFFFF0;	//PA8���֮ǰ������
	GPIOA->CRH|=0X0000000B;	//���ù������ 
	
	TIM1->ARR=arr;			//�趨�������Զ���װֵ 
	TIM1->PSC=psc;			//Ԥ��Ƶ������
  
	TIM1->CCMR1|=7<<4;  	//CH1 PWM2ģʽ		 
	TIM1->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM1->CCER|=1<<0;   	//OC1 ���ʹ��	   
	TIM1->BDTR|=1<<15;   	//MOE �����ʹ��	   

	TIM1->CR1=0x0080;   	//ARPEʹ�� 
	TIM1->CR1|=0x01;    	//ʹ�ܶ�ʱ��1 			
} 


