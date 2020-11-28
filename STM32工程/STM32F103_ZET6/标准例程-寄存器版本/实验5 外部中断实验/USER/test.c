#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "beep.h"
#include "exti.h" 	 
//ALIENTEK战舰STM32开发板实验5
//外部中断 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
int main(void)
{					   
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200); 	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口 
	BEEP_Init();		 	//初始化蜂鸣器IO
	EXTIX_Init();         	//初始化外部中断输入 
	LED0=0;					//先点亮红灯
	while(1)
	{	    
		printf("OK\r\n");	
		delay_ms(1000);	  
	}	 
}

