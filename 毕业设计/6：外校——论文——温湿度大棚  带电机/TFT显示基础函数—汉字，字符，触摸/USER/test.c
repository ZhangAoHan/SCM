#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "display.h"
#include "control.h"
#include "date.h"
#include "control.h"
#include "touch.h"  
#include "w25q128.h"
#include "text.h"
#include "at24c02.h" 

u8 page=0;
u8 temperature;  	    
u8 humidity;  	
u8 temperature2;  	    
u8 humidity2;  
u8 t1,t2,t3,t4,t5;
u8 tt1,tt2,tt3,tt4,tt5;
u8 h1,h2,h3,h4,h5;
u8 hh1,hh2,hh3,hh4,hh5;
int main(void)
{				 

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	while(font_init()) 			//检查字库
	{;}  
	LCD_Init_Display();
	while(DHT11_Init())	//DHT11初始化	
	{;}
	while(DHT12_Init())	//DHT11初始化	
	{;}
	Io_In_Out();
	Adc_Init();
	Adc2_Init();
	Adc3_Init();
	Adc4_Init();
	Adc0_Init();
//	PWM_Init(200,7199);      //舵机控制需要20ms的脉冲即50HZ    50=72 000 000/psc*arr 
	PWM_Init(5000,0); 	
	TIM3_Int_Init(9999,7199);
	LCD_Clear(WHITE);	
  	while(1)
	{
		use_control();
	}	 
} 






