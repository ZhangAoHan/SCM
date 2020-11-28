#include "Motor.h"

void TIME3_PWM_init(u16 psc,u16 arr)   //ʹ�ö�ʱ��3ͬʱ���4·PWM
{
	RCC->APB1ENR |=1<<1;     //ʹ�ܶ�ʱ��3
	TIM3->CR1 |=1<<0;        //ʹ�ܼ���������ʱ����ʼʱ��Ϊ72M�����������ϼ���
	TIM3->CR1 |=1<<7;        //ARPEʹ�� 
	TIM3->PSC =psc;        
	TIM3->ARR =arr;        
	TIM3->CCMR1 &=0X0000;   //ͨ��1  2����Ϊ���
	TIM3->CCMR2 &=0X0000;   //ͨ��3  4����Ϊ���
	TIM3->CCMR1 |=0X7878;   //ͨ��1 2����ΪPWM2ģʽ 
	TIM3->CCMR2 |=0X7878;   //ͨ��3 4����ΪPWM2ģʽ 
	TIM3->CCER |=0X3333;   //ͨ��1 2 3 4  �͵�ƽ��Ч     
}
void IO_init(void)
{
	RCC->APB2ENR |=0X000C;   //ʹ��GPIOA B
	GPIOA->CRL &=0X00FFFFFF;  
	GPIOA->CRH &=0X0000FFFF; 
	GPIOA->CRL |=0XBB000000;  //��ʱ������Ƚ���Ҫ����Ϊ�����������
	GPIOA->CRH |=0X33330000; 
	GPIOB->CRL &=0XFFFFFF00;  
	GPIOB->CRL |=0X000000BB;
}


