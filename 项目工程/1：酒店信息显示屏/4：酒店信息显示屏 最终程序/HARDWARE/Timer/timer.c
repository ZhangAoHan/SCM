#include "timer.h"


void TIM2_Int_Init(u16 arr,u16 psc)
{
RCC->APB1ENR |= 1<<0;//TIM2ʱ��ʹ��


TIM2->ARR = arr;
TIM2->PSC = psc;


TIM2->DIER |= 1<<0;//��������ж�
TIM2->DIER |= 1<<6;//ʹ�ܴ����ж�


 MY_NVIC_Init(1,2,TIM2_IRQn,2);//��ռ1�������ȼ�2����2


TIM2->CR1 |= 1<<0;//ʹ�ܶ�ʱ��

}

//��ʱ��2�жϷ������  
void TIM2_IRQHandler(void)
{      
   
if(TIM2->SR&0X0001)//����ж�
{

}   
TIM2->SR&=~(1<<0);//����жϱ�־λ 
   
}


