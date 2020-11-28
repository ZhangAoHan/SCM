#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "beep.h" 
#include "key.h"	 	 
//ALIENTEK战舰STM32开发板实验4
//串口 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

u8 res=0x00;	
int main(void)
{								  

	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600); 	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口 
	LED0=0;
 	while(1)
	{
		switch(res)
		{
			case 0x01:LED0=1;break;
			case 0x02:LED0=0;break;
		}
	}		 
}

