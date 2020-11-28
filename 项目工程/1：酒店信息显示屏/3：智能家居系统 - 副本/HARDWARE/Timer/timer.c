#include "timer.h"


void TIM2_Int_Init(u16 arr,u16 psc)
{
RCC->APB1ENR |= 1<<0;//TIM2时钟使能


TIM2->ARR = arr;
TIM2->PSC = psc;


TIM2->DIER |= 1<<0;//允许更新中断
TIM2->DIER |= 1<<6;//使能触发中断


 MY_NVIC_Init(1,2,TIM2_IRQn,2);//抢占1，子优先级2，组2


TIM2->CR1 |= 1<<0;//使能定时器

}

//定时器2中断服务程序  
void TIM2_IRQHandler(void)
{      
   
if(TIM2->SR&0X0001)//溢出中断
{

}   
TIM2->SR&=~(1<<0);//清除中断标志位 
   
}


