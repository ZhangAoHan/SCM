#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "key.h"
#include "wdg.h" 	  
//ALIENTEK战舰STM32开发板实验7
//窗口看门狗 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
int main(void)
{					   
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200); 	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口  
	KEY_Init();         	//初始化与按键连接的硬件接口
 	LED0=0;				 	//点亮DS0
	delay_ms(300);			//延时300ms,让人可以看到DS0亮的状态
 	WWDG_Init(0X7F,0X5F,3);	//计数器值为7f,窗口寄存器为5f,分频数为8	   
 	while(1)
	{
		LED0=1;			  	 //灭DS1
	}  		 
}

