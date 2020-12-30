#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"
#include "24l01.h"
#include "control.h"
#include "timer.h"

u8 tmp_buf[33];

u8 temperature;  	    
u8 humidity; 
u16 adc_mq2;
u16 adc_gm;
u16 adc_tr;
unsigned char SN[4]; //卡号
u8 page=0;
u16 t1;
u16 t2;
u16 t3;
u16 time1;
u16 time2;
u16 time3;
int main(void)
{				 

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	LED_Init();
	NRF24L01_Init();    		//初始化NRF24L01 

	while(font_init()) 			//检查字库
	{
	LCD_ShowString(30,50,200,16,16,"TFT Error");
	}  
		Show_Str(6,50,96,24,"字库完整",24,0);
		while(NRF24L01_Check())
	{
		LCD_ShowString(30,130,200,16,16,"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	LCD_ShowString(30,130,200,16,16,"NRF24L01 OK"); 	 
		
		LCD_Clear(WHITE);
	PWM_Init(10000,0);      //舵机控制需要20ms的脉冲即50HZ    50=72 000 000/psc*arr 
	TIM3_Int_Init(9999,7199);//10Khz的计数频率，100ms
		delay_ms(100);
	NRF24L01_RX_Mode();		
	
  	while(1)
	{

		user_control();
	}	 
} 






