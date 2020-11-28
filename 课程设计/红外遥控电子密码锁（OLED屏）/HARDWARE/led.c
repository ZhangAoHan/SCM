#include "led.h"
#include "sys.h"
void led_init(void)
{
	RCC->APB2ENR|=1<<2;  //ʹ��GPIOAʱ��
	RCC->APB2ENR|=1<<4;  //ʹ��GPIOCʱ��
	GPIOA->CRL&=0xffff0f0f;    
	GPIOA->CRL|=0x00003030;    //����GPIOA1 3���������������ٶ�Ϊ50M
	GPIOA->ODR|=0x0006;    //��GPIOA1��GPIOA3��ʼ���Ϊ�ߣ���
	GPIOC->CRH&=0x0f0fffff;    
	GPIOC->CRH|=0x30300000;    //����GPIOC15���������������ٶ�Ϊ50M
	GPIOC->ODR|=0xa000;    //��GPIOC15��ʼ���Ϊ�ߣ���
}

