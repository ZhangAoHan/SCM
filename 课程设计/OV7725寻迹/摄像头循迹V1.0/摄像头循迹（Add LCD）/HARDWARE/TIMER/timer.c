#include "timer.h"
#include "led.h"
#include "delay.h"
#include "usart.h"

extern MOTOR GmLeft;//定义并初始化左电机状态
extern MOTOR GmRight ;//定义并初始化右电机状态

void Timer2_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
 	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM 中断源
		TIM_IT_Trigger,   //TIM 触发中断源 
		ENABLE  //使能
		);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel =  TIM2_IRQn;  //TIM2中断	 TIM3_IRQn |
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0 ;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);

	
}
void TIM2_IRQHandler(void) 
{	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
	
		   
			switch (GmLeft.cState)
			{
				case MOTOR_STOP:						 /*	停止，同时清零脉冲 */
					GmLeft.ulPulse     =     0;
					GmLeft.ulPulseCtr  =     0;
					 break;

			    case MOTOR_RUN:
					 StepLeft();
					 break;

				default:
					 break;
			}

			/*
			*	是否完成任务判断
			*/
			if(GmLeft.cState  ==  MOTOR_RUN)
			{
				GmLeft.ulPulseCtr++;
				if(GmLeft.ulPulseCtr  >=   GmLeft.ulPulse)
				{
					GmLeft.cState  =  MOTOR_STOP;
					GmLeft.ulPulseCtr =  0;
					GmLeft.ulPulse =  0;
				    //printf("ulPulseCtr = %d \n",GmRight.ulPulseCtr);
				}
			}
			
		}
}
/**/


/*
	功 能：控制步进电机
	调 用：外部调用 ，在步进电机初始化函数中使用
*/
void Timer3_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3 , //TIM2
		TIM_IT_Update  |  //TIM 中断源
		TIM_IT_Trigger,   //TIM 触发中断源 
		ENABLE  //使能
		);

	NVIC_Configuration(); 	 //设置NVIC中断分组

	NVIC_InitStructure.NVIC_IRQChannel =  TIM3_IRQn;  //TIM3中断	 TIM3_IRQn |
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);

}

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源

			switch (GmRight.cState)
			{
				case MOTOR_STOP:						 /*	停止，同时清零脉冲 */
					GmRight.ulPulse     =     0;
					GmRight.ulPulseCtr  =     0;
					 break;

			    case MOTOR_RUN:
					 StepRight();
					 break;

				default:
					 break;
			}

			/*
			*	是否完成任务判断
			*/
			if(GmRight.cState  ==  MOTOR_RUN)
			{
				GmRight.ulPulseCtr++;
				if(GmRight.ulPulseCtr  >=   GmRight.ulPulse)
				{
					GmRight.cState  =  MOTOR_STOP;
					GmRight.ulPulseCtr =  0;
					GmRight.ulPulse =  0;
				    //printf("ulPulseCtr = %d \n",GmRight.ulPulseCtr);
				}
			}
		}
}











