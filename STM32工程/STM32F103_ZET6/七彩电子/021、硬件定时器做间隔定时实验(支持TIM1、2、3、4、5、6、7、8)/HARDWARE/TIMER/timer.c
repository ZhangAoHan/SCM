#include "timer.h"
#include "led.h"





/*************************** 文件说明 *******************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 






//先科普一下
/* 

103的定时器分为3类

高级控制定时器:  TIM1 TIM8           (时钟来源于APB2 * 1 , 最大72M * 1 =72M )
通用定时器    :  TIM2 TIM3 TIM4 TIM5 (时钟来源于APB1 * 2 , 最大36M * 2 =72M )
基本定时器    :  TIM6 TIM7           (时钟来源于APB1 * 2 , 最大36M * 2 =72M )

不是所有的F103单片机都拥有全部定时器

STM32F103C8         TIM1 TIM2 TIM3 TIM4 
STM32F103RC及以上   TIM1 TIM2 TIM3 TIM4 TIM5 TIM6 TIM7 TIM8
STM32F103xF及以上   TIM1 TIM2 TIM3 TIM4 TIM5 TIM6 TIM7 TIM8 TIM9 TIM10 TIM11 TIM12 TIM13 TIM14

*/



TIM_TypeDef * TIM[]={TIM1,TIM2,TIM3,TIM4,TIM5,TIM6,TIM7,TIM8};
u8 TIM_IRQChannel[]={TIM1_UP_IRQn,TIM2_IRQn,TIM3_IRQn,TIM4_IRQn,TIM5_IRQn,TIM6_IRQn,TIM7_IRQn,TIM8_UP_IRQn};





/*
功能: 根据微妙时间初始化定时器为间隔定时器并启动中断
TIM_Index: 对应硬件定时器的序号,只支持1~8,9~14只有103xF及xG系列才有,未做支持
nus : 要初始化间隔定时器的间隔 ,单位为us,例如1000则为1ms中断一次,最大支持65535us,即65.535ms
返回值: 无
*/
void TIM_SetInterval(u8 TIM_Index,u32 nus){
	
	if(nus==0){
		return ;
	}
	TIM_Init(TIM_Index,72-1,nus-1);
}



/*
功能: 根据分频系数和计数溢出值初始化定时器为间隔定时器并启动中断
TIM_Index: 对应硬件定时器的序号,只支持1~8,9~14只有103xF及xG系列才有,未做支持
nus : 要初始化间隔定时器的间隔 ,单位为us,例如1000则为1ms中断一次,最大支持65535us,即65.535ms
返回值: 无
*/
void TIM_Init(u8 TIM_Index,u16 Prescaler,u16 Period){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	if(TIM_Index>=2&&TIM_Index<=7){//TIM2 ~ TIM7
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2<<(TIM_Index-2), ENABLE); //时钟使能
	}
	else if(TIM_Index==1){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能
	}
	else if(TIM_Index==8){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //时钟使能
	}
	else {
		return ;//其他的不支持
	}
		
	
	//定时器初始化
		
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Period = Period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//
	TIM_TimeBaseInit(TIM[TIM_Index-1], &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM[TIM_Index-1],TIM_IT_Update,ENABLE ); //使能指定的TIM中断,允许更新中断

	
	TIM_ARRPreloadConfig(TIM[TIM_Index-1],DISABLE);
	
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQChannel[TIM_Index-1];  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM[TIM_Index-1], ENABLE);  //使能TIMx		
}



#if 0
//定时器中断服务程序
void TIM1_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //清除TIMx更新中断标志 
			//LED1=!LED1;
		}
}
#endif



#if 1
//定时器中断服务程序
void TIM2_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
			//LED1=!LED1;
		}
}
#endif



#if 1
//定时器中断服务程序
void TIM3_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
			//LED1=!LED1;
		}
}
#endif



#if 1
//定时器中断服务程序
void TIM4_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
			//LED1=!LED1;
		}
}
#endif



#if 1
//定时器中断服务程序
void TIM5_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //清除TIMx更新中断标志 
			//LED1=!LED1;
		}
}
#endif



#if 1
//定时器中断服务程序
void TIM6_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //清除TIMx更新中断标志 
			//LED1=!LED1;
		}
}
#endif



#if 1
//定时器中断服务程序
void TIM7_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIMx更新中断标志 
			//LED1=!LED1;
		}
}
#endif



#if 1
//定时器中断服务程序
void TIM8_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM8, TIM_IT_Update  );  //清除TIMx更新中断标志 
			//LED1=!LED1;
		}
}
#endif

























