#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"  
#include "exti.h" 
//ALIENTEK Mini STM32开发板范例代码4
//外部中断实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{			
	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);	    //延时初始化
	uart_init(72,9600); //串口初始化 
	LED_Init();		  	//初始化与LED连接的硬件接口
	EXTI_Init();		//外部中断初始化
	LED0=0;				//点亮LED
	while(1)
	{	    
		printf("OK\r\n");	
		delay_ms(1000);	  
	} 
}














