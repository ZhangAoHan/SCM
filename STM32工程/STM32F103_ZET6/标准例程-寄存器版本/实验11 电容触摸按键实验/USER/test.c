#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "tpad.h"
//ALIENTEK战舰STM32开发板实验11
//电容触摸按键 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  
int main(void)
{					   
	u8 t=0;  	
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200);	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
 	TPAD_Init(6);			//初始化触摸按键
   	while(1)
	{					  						  		 
 		if(TPAD_Scan(0))	//成功捕获到了一次上升沿(此函数执行时间至少15ms)
		{
			LED1=!LED1;		//LED1取反
		}
		t++;
		if(t==15)		 
		{
			t=0;
			LED0=!LED0;		//LED0取反,提示程序正在运行
		}
		delay_ms(10);
	}
}


