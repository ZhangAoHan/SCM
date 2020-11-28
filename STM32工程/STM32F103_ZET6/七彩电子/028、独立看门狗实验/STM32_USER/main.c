/*  main.c  */


#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"
#include "led.h"
#include "iwdg.h"


/*************************** 文件说明 *******************************/
//作者:七彩光子
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 




/*
功能说明:
    独立看门狗测试例程,独立看门狗函数封装,并请提供了常用复位时间设置函数。
		注意,看门狗复位时间由于时钟源精度等原因,所提供的时间只是一个大概值,喂狗时请注意留有时间余量
*/




int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	USART1_Init(115200);//串口1初始化
	USART_SendString(USART1,(u8*)"System start...\r\n");
	LED_Init();
	IWDG_Init_2s();
	delay_ms(1000);
	LED_ON(LED1);//点亮LED1,如果不喂狗,看门狗会在1s后复位系统使LED1关闭,因此LED1会间隔1s闪烁
	
	while(1)
	{
		//IWDG_Feed();//喂狗,取消注释则系统停止复位,LED1不再闪烁
		delay_ms(1000);
	}
}

































