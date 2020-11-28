#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "ds18b20.h"   
//ALIENTEK Mini STM32开发板范例代码23
//DS18B20数字温度传感器实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

int main(void)
{		
	u8 t=0;			    
	short temperature;   
 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD  
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"DS18B20 TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/12");		  
 	while(DS18B20_Init())	//DS18B20初始化	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	LCD_ShowString(60,130,200,16,16,"DS18B20 OK");
	POINT_COLOR=BLUE;//设置字体为蓝色 
 	LCD_ShowString(60,150,200,16,16,"Temp:   . C");	 
	while(1)
	{	    	    
 		if(t%10==0)//每100ms读取一次
		{									  
			temperature=DS18B20_Get_Temp();	
			if(temperature<0)
			{
				LCD_ShowChar(60+40,150,'-',16,0);			//显示负号
				temperature=-temperature;					//转为正数
			}else LCD_ShowChar(60+40,150,' ',16,0);			//去掉负号
			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//显示正数部分	    
   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//显示小数部分 		   
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}



















