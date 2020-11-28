#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"
#include "usmart.h"
//ALIENTEK战舰STM32开发板实验14
//USMART调试组件 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  

//LED状态设置函数
void led_set(u8 sta)
{
	LED1=sta;
} 
//函数参数调用测试函数
void test_fun(void(*ledset)(u8),u8 sta)
{
	ledset(sta);
} 
int main(void)
{					    
  	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200);	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	usmart_dev.init(72); 	//初始化USMART				 	
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();				//初始化LCD
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"WarShip STM32 ^_^");	
	LCD_ShowString(30,70,200,16,16,"USMART TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/14");	   
  	while(1) 
	{		 	  
		LED0=!LED0;					 
		delay_ms(500);	
	}
}























