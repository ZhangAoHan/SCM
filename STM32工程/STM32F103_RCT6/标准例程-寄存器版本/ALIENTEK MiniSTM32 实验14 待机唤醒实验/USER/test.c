#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "wkup.h" 
//ALIENTEK Mini STM32开发板范例代码14
//待机唤醒实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
int main(void)
{			   
  	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
 	WKUP_Init();			//初始化WK_UP按键，同时检测是否正常开机？
	LCD_Init();			   	//初始化LCD 			 	
 	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"Mini STM32");	
	LCD_ShowString(30,70,200,16,16,"WKUP TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/3/8");	 
	while(1)
	{
		LED0=!LED0;
		delay_ms(250);
	}											    
}	









