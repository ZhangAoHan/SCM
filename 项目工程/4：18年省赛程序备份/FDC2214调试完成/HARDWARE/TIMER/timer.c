#include "timer.h"
#include "sys.h"
#include "led.h"
#include "sys.h"


void TIM3_Config(uint16_t Period,uint16_t Prescaler,uint16_t Seize_priority,uint16_t Sub_priority)
{
	//定义结构体变量
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;		//定义定时器参数初始化结构体变量
	NVIC_InitTypeDef        NVIC_InitStructure;				//定义中断优先级配置结构体变量
	//时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能TIM3时钟，挂载在APB1总线
	//TIM3参数初始化
	TIM_TimeBaseStructure.TIM_Period=Period;			//设置自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler=Prescaler;//设置时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	    //时钟分频1
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //TIM向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	//初始化TIM3
	//使能更新中断并软件清除更新中断标志位
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//清除TIM3更新中断标志位
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//使能TIM3更新中断
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	//定义初始化时哪个中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=Seize_priority;//抢占优先级为0（级别高于子优先级）2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=Sub_priority;//子优先级为0（数值越小优先级越高）0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//IRQ此通道使能
	NVIC_Init(&NVIC_InitStructure);//初始化中断优先级NVIC
	//使能这个内置外设TIM3
	TIM_Cmd(TIM3,ENABLE);//使能TIM3
	
	
}


