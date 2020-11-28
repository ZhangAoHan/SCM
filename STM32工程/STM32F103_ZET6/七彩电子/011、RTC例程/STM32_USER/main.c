/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "rtc.h"



/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 
 


int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	USART1_Init(115200);//串口1初始化
	
	
	while(RTC_Init())//RTC初始化
	{
		delay_ms(500);
		delay_ms(500);
		LED_TOGGLE(LED0);
		LED_TOGGLE(LED1);
		printf("RTC Init Failed!\r\n");
	}
	
	printf("RTC Init OK !\r\n");
	
	//RTC_Set(2017,12,4,12,4,30);//设置时间		
	
	
	while(1)
	{
		
		printf("Time:%d-%d-%d %d:%02d:%02d\r\n",\
					calendar.w_year,\
					calendar.w_month,\
					calendar.w_date,\
					calendar.hour,\
					calendar.min,\
					calendar.sec);//输出时间
		
		delay_ms(1000);
		LED_TOGGLE(LED1);
	}
}




