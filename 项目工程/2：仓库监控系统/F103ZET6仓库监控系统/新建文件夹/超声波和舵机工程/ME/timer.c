#include "timer.h"
#include "sys.h" //��Ϊ�����ж����ȼ���Ҫ����sys.c�еĺ���

void PWM_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
	GPIOA->CRL&=0XF0FFFFFF;	//PA6���֮ǰ������
	GPIOA->CRL|=0X0B000000;	//���ù������
	TIM3->ARR=arr;             //�趨�������Զ���װֵ 
	TIM3->PSC=psc;             //Ԥ��Ƶ����Ƶ
	TIM3->CCMR1|=6<<4;         //CH1 PWM1ģʽ		 
	TIM3->CCMR1|=1<<3;         //CH1Ԥװ��ʹ��	    
	TIM3->CCER|=1<<0;          //CH1���ʹ��	
	TIM3->CR1=0x0080;          //ARPEʹ�� 
	TIM3->CR1|=0x01;          //ʹ�ܶ�ʱ��3	
}

