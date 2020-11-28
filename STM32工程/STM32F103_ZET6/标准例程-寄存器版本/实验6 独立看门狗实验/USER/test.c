#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "key.h"
#include "wdg.h" 	  
//ALIENTEK战舰STM32开发板实验6
//独立看门狗 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
int main(void)
{					   
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200); 	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口  
	KEY_Init();         	//初始化与按键连接的硬件接口
 	delay_ms(500);			//延时500ms,让人可以看到DS0灭的状态
 	IWDG_Init(4,625);    	//与分频数为64,重载值为625,溢出时间为1s	   
	LED0=0;				 	//点亮DS0
	while(1)
	{
		if(KEY_Scan(0)==WKUP_PRES)//如果WK_UP按下,则喂狗
		{
			IWDG_Feed();
		}
		delay_ms(10);
	}		 
}

