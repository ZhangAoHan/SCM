#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "wdg.h" 
//ALIENTEK Mini STM32开发板范例代码6
//窗口看门狗实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{			
  	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
	LED0=0;
	delay_ms(300);	  
	WWDG_Init(0X7F,0X5F,3);//计数器值为7f,窗口寄存器为5f,分频数为8	   
 	while(1)
	{
		LED0=1;			  	   
	}
}














