#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "touch.h"  
#include "w25qxx.h"  
#include "text.h"	 
#include "csb.h"   
#include "control.h"   
u32 Distance;  
float m1,m2;
int main(void)
{				 
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	POINT_COLOR=RED;
	tp_dev.init();			//触摸屏初始化 
	TIM2_Cap_Init(0XFFFF,72-1);	
	TIM3_Int_Init(999,7199);//时钟周期0.1ms，
	while(font_init()) 			//检查字库
	{ 	
		LCD_Clear(WHITE);		   	//清屏
 		POINT_COLOR=RED;			//设置字体为红色	   	   	  
		LCD_ShowString(30,50,200,16,16,"WarShip STM32");								 						    
		LCD_ShowString(30,90,200,16,16,"Font Updating...");	  
		LCD_ShowString(30,110,200,16,16,"Font Update Success!   ");
		delay_ms(1500);	
		LCD_Clear(WHITE);//清屏	       
	}  
			TFT_S_Display();
		while(1)
	{
		 
		TFT_Display();
	}
} 



//		printf("t:%d\r\n",t);


