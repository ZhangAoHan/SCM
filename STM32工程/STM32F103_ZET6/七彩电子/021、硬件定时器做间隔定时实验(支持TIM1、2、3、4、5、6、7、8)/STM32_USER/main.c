/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"
#include "led.h"
#include "timer.h"


/*************************** 文件说明 *******************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 


u32 timCnt=0;


#define INTERVAL_TIME  (1000)      //定时时间,单位ms



int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	USART1_Init(115200);//串口1初始化
	LED_Init();
	TIM_SetInterval(1,50000);//50ms
	
	while(1)
	{
		if(timCnt>=(INTERVAL_TIME/50)){//定时时间到
			timCnt=0;
			
			LED1=!LED1;
			
		}
	}
}




#if 1
//定时器中断服务程序
void TIM1_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET){  //检查TIM更新中断发生与否
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //清除TIMx更新中断标志 
		//LED1=!LED1;
		if(timCnt<(INTERVAL_TIME/50)){
			timCnt++;
		}
	}
}
#endif






























