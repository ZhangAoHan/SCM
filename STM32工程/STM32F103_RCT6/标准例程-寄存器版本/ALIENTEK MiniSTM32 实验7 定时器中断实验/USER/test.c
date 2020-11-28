#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "timer.h" 
//ALIENTEK Mini STM32开发板范例代码7
//定时器中断实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{			
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
	TIM3_Int_Init(5000,7199);//10Khz的计数频率，计数到5000为500ms  
   	while(1)
	{
		LED0=!LED0;
		delay_ms(200);		   
	}
}














