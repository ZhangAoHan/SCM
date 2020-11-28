#include "timer.h"
#include "sys.h"

void Timer_init(u16 arr,u16 psc)
{
	RCC->APB1ENR |=1<<1;       //ʹ�ܶ�ʱ��3
	TIM3->CR1 |=1<<0;          //ʹ�ܼ���������ʱ����ʼʱ��Ϊ72M�����������ϼ���
	TIM3->CR1 |=0X0080;
  	TIM3->PSC =psc;  
	TIM3->ARR =arr; 
	
	TIM3->CCMR1 |=7<<4;        //ͨ��1����
	TIM3->CCMR1 |=1<<3;
	TIM3->CCER  |=1<<0;        //ͨ��1��Ч��ƽ�������ã�TIM3->CCER=1��pwmΪ�͵�ƽ��Ч��=3��pwmΪ�ߵ�ƽ��Ч��
	
	TIM3->CCMR1 |=7<<12;       //ͨ��2����
	TIM3->CCMR1 |=1<<11;
	TIM3->CCER  |=1<<4;
	
	TIM3->CCMR2 |=7<<4;        //ͨ��3����
	TIM3->CCMR2 |=1<<3;
	TIM3->CCER  |=1<<8;
	
	TIM3->CCMR2 |=7<<12;       //ͨ��4����
	TIM3->CCMR2 |=1<<11;
	TIM3->CCER  |=1<<12;
}

void LED_init(void)
{
	
	RCC->APB2ENR|=1<<3;        //ʹ��GPIOB
	GPIOB->CRL&=0XFFFFFF00;    //ͨ��3 GPIOB0,�����������������ٶ�50M
	GPIOB->CRL|=0X000000BB;    //ͨ��4 GPIOB1,�����������������ٶ�50M 
    GPIOB->ODR|=1<<0;          //����GPIOB0Ϊ���ģʽ
	GPIOB->ODR|=1<<1;          //����GPIOB0Ϊ���ģʽ
	
	RCC->APB2ENR|=1<<2;        //ʹ��GPIOA
	GPIOA->CRL&=0X00FFFFFF;    //ͨ��1 GPIOA6,�����������������ٶ�50M
	GPIOA->CRL|=0XBB000000;    //ͨ��2 GPIOA7,�����������������ٶ�50M
	GPIOA->ODR|=1<<6;         //����GPIOA6Ϊ���ģʽ
	GPIOA->ODR|=1<<7;         //����GPIOA7Ϊ���ģʽ
}




