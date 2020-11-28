#include "sys.h"   
#include "motor.h"  

void TIM3_init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_init;  
	TIM_TimeBaseInitTypeDef TIM_init;  //经检查，定时器配置没问题
	TIM_OCInitTypeDef TIM_oc_init;   //经检查，OC1通道配置寄存器没问题
//IO口配置函数（ 必须遵循重映射寄存器 ）	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_init.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
  GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_init); 
//定时器3初始化函数
  TIM_init.TIM_Period = arr;
  TIM_init.TIM_Prescaler =psc;
  TIM_init.TIM_ClockDivision = 0;
  TIM_init.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_TimeBaseInit(TIM3, &TIM_init); 
//PWM配置函数	
  TIM_oc_init.TIM_OCMode = TIM_OCMode_PWM2; 
  TIM_oc_init.TIM_OutputState = TIM_OutputState_Enable;   
  TIM_oc_init.TIM_OCPolarity = TIM_OCPolarity_High;    
  TIM_OC1Init(TIM3, &TIM_oc_init); 
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM3, &TIM_oc_init); 
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
  TIM_Cmd(TIM3, ENABLE); //使能 TIM3
}
