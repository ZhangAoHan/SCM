#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h" 
//ALIENTEK Mini STM32开发板范例代码2
//按键输入实验		   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{		 
	vu8 t;	  
	Stm32_Clock_Init(9); 	//系统时钟设置
	delay_init(72);	     	//延时初始化 
	LED_Init();		  	 	//初始化与LED连接的硬件接口
	KEY_Init();          	//初始化与按键连接的硬件接口
	LED0=0;					//点亮LED
	while(1)
	{
		t=KEY_Scan(0);		//得到键值
		switch(t)
		{				 
			case KEY0_PRES:
				LED0=!LED0;
				break;
			case KEY1_PRES:
				LED1=!LED1;
				break;
			case WKUP_PRES:				
				LED0=!LED0;
				LED1=!LED1;
				break;
			default:
				delay_ms(10);	
		} 
	}		 
}

























