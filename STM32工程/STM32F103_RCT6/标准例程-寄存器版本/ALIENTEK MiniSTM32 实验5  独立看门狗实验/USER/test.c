#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"  
#include "key.h"  
#include "wdg.h" 
//ALIENTEK Mini STM32开发板范例代码5
//独立看门狗实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{			
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
	KEY_Init();          //按键初始化	 
	delay_ms(300);   	 //让人看得到灭
	IWDG_Init(4,625);    //与分频数为64,重载值为625,溢出时间为1s	   
	LED0=0;				 //点亮LED0
	while(1)
	{
		if(KEY_Scan(0)==WKUP_PRES)IWDG_Feed();//如果WK_UP按下,则喂狗
		delay_ms(10);
	};
}














