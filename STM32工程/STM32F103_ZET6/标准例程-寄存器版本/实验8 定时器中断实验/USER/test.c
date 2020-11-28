#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "timer.h" 
//ALIENTEK战舰STM32开发板实验8
//定时器中断 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
int main(void)
{					   
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200); 	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
 	 
   	while(1)
	{
		LED0=!LED0;
		delay_ms(200);		   
	}	
}	 

