#include "timer.h"
#include "sys.h" //��Ϊ�����ж����ȼ���Ҫ����sys.c�еĺ���

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
