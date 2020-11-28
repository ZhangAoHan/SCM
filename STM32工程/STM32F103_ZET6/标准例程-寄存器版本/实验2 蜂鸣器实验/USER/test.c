#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "beep.h" 	 
//ALIENTEK战舰STM32开发板实验2
//蜂鸣器 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
int main(void)
{				  
	Stm32_Clock_Init(9); 	//系统时钟设置
	delay_init(72);	    	//延时初始化
	LED_Init();		  	 	//初始化与LED连接的硬件接口
	BEEP_Init();         	//初始化蜂鸣器端口
	while(1)
	{
		LED0=0;				//点亮DS0
		BEEP=0;		  		//关闭蜂鸣器
		delay_ms(300);
		LED0=1;	  			//关闭DS0
		BEEP=1;  			//打开蜂鸣器
		delay_ms(300);
	}	 
}








