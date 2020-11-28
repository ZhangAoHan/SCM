#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "oled.h" 
//ALIENTEK Mini STM32开发板范例代码10
//OLED显示实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 
int main(void)
{			 
 	u8 t=0;	    	
 	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);	    //延时初始化
	uart_init(72,9600); //串口初始化 
	LED_Init();		  	//初始化与LED连接的硬件接口 
	OLED_Init();		//初始化OLED
  	OLED_ShowString(0,0,"ALIENTEK",24);  
	OLED_ShowString(0,24, "0.96' OLED TEST",16);  
 	OLED_ShowString(0,40,"ATOM 2014/3/7",12);  
 	OLED_ShowString(0,52,"ASCII:",12);  
 	OLED_ShowString(64,52,"CODE:",12);  
	OLED_Refresh_Gram();//更新显示到OLED	 
	t=' ';  
	while(1) 
	{		
		OLED_ShowChar(36,52,t,12,1);//显示ASCII字符	
		OLED_ShowNum(94,52,t,3,12);	//显示ASCII字符的码值    
		OLED_Refresh_Gram();//更新显示到OLED
		t++;
		if(t>'~')t=' ';  
		delay_ms(500);
		LED0=!LED0;
	}	  
}











