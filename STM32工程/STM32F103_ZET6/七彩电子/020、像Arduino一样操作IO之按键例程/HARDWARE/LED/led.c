
//
#include "led.h"

/***********************************************************************/
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/ 



//2017.9.28  V1.0

//2017.12.10 v1.1  修改高电平驱动为低电平驱动


//初始化LED0和LED1为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
	
 RCC_APB2PeriphClockCmd(LED0_GPIO_RCC_CLK|LED1_GPIO_RCC_CLK, ENABLE);	 //使能PB,PE端口时钟

 GPIO_InitStructure.GPIO_Pin = LED0_PIN;				       //LED0端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(LED0_GPIO, &GPIO_InitStructure);					   //根据设定参数初始化LED0
 GPIO_SetBits(LED0_GPIO,LED0_PIN);						         //LED0输出高

 GPIO_InitStructure.GPIO_Pin = LED1_PIN;	    		     //LED1端口配置, 推挽输出
 GPIO_Init(LED1_GPIO, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(LED1_GPIO,LED1_PIN); 						         //LED1输出高 
}
 
