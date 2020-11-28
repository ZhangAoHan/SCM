#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "adc.h"
#include "lsens.h"
//ALIENTEK战舰STM32开发板 实验19
//光敏传感器 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  

int main(void)
{		 	
 	u8 adcx; 
  	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200);	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
  	LCD_Init();				//初始化LCD
	Lsens_Init(); 			//初始化光敏传感器
	POINT_COLOR=RED;//设置字体为红色  	
	//显示提示信息											      
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"LSENS TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/14");	  
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(30,130,200,16,16,"LSENS_VAL:");	             
	while(1)
	{
		adcx=Lsens_Get_Val();
		LCD_ShowxNum(30+10*8,130,adcx,3,16,0);//显示ADC的值 
		LED0=!LED0;
		delay_ms(250);	
	}
}


