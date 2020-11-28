/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"


/*************************** 文件说明 *******************************/
//ezio 单片机IO简明操作函数封装,不用声明和填写冗长的结构体,一个函数搞定
//像Arduino一样操作IO
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 


#define LED0 PB5
#define LED1 PE5 


//key0 PE4
//key1 PE3
//key2 PE2
//key3/key_up PA0 



int main(void)
{
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	USART1_Init(115200);//串口1初始化

	Pin_ModeSet(LED0,OUTPUT|OUT_H);//LED0初始化
	Pin_ModeSet(LED1,OUTPUT|OUT_H);//LED1初始化

	Pin_ModeSet(PE4,INPUT);//KEY0 上拉
	Pin_ModeSet(PE3,INPUT);//KEY1 上拉
	Pin_ModeSet(PE2,INPUT);//KEY2 上拉
	Pin_ModeSet(PA0,INPUT_PD);////KEY3高电平有效,平时下拉
	
	while(1)
	{
		//KEY0
		if(Pin_Read(PE4)==0){
			delay_ms(10);
			if(Pin_Read(PE4)==0){
				Pin_Toggle(LED1);
				while(Pin_Read(PE4)==0);
			}
		}
		//KEY1
		if(Pin_Read(PE3)==0){
			delay_ms(10);
			if(Pin_Read(PE3)==0){
				Pin_Toggle(LED1);
				while(Pin_Read(PE3)==0);
			}
		}
		//KEY2
		if(Pin_Read(PE2)==0){
			delay_ms(10);
			if(Pin_Read(PE2)==0){
				Pin_Toggle(LED1);
				while(Pin_Read(PE2)==0);
			}
		}
		//KEY3
		if(Pin_Read(PA0)==1){
			delay_ms(10);
			if(Pin_Read(PA0)==1){
				Pin_Toggle(LED1);
				while(Pin_Read(PA0)==1);
			}
		}
	}
}




