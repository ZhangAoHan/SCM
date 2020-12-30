#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"	
#include "adc_dht11.h"
#include "control.h"
#include "display.h"
u8 page=0;   //0x0     
int main(void)
{				 

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	Adc_Init();
	init_display();
  	while(1)
	{
		 use_control();
	}	 
} 






