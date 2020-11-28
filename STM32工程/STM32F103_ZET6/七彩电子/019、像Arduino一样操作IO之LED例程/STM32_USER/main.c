/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"


/*************************** 文件说明 *******************************/
//ezio 单片机IO简明操作函数封装,不用声明和填写冗长的结构体,一个函数搞定
//像Arduino一样操作IO
//作者:七彩光子
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 


#define LED0 PB5
#define LED1 PE5 


int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	USART1_Init(115200);//串口1初始化

	Pin_ModeSet(LED0,OUTPUT);//LED0初始化
	Pin_ModeSet(PE5,OUTPUT);//LED1初始化

	while(1)
	{
		Pin_Write(LED0,0);//低电平点亮
		Pin_Write(LED1,1);//高电平熄灭
		delay_ms(500);
		Pin_Write(PB5,1);//高电平熄灭
		Pin_Write(PE5,0);//低电平点亮
		delay_ms(500);
		Pin_Toggle(PB5);
		Pin_Toggle(PE5);
		delay_ms(500);
		Pin_WriteHigh(PB5);
		Pin_WriteLow(PE5);
		delay_ms(500);
	}
}




