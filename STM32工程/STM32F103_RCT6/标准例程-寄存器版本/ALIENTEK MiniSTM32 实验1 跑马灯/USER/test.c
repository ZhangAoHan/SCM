#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
//ALIENTEK Mini STM32开发板范例代码1
//跑马灯实验		   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{		 
	Stm32_Clock_Init(9); 	//系统时钟设置
	delay_init(72);	     	//延时初始化
	LED_Init();		  	 	//初始化与LED连接的硬件接口    
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(300);
		LED0=1;
		LED1=0;
		delay_ms(300);
	}	 
}

























