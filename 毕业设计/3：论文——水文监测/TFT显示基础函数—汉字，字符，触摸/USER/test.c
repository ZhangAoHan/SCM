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
u8 door=0;
u8 times=0;
unsigned char SN[4]={0,0,0,0}; //卡号
unsigned char NEW_SN[4]={0,0,0,0}; //卡号
unsigned char OLD_SN[4]={0,0,0,0}; //卡号
int main(void)
{				 

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	NRF24L01_Init();    		//初始化NRF24L01 
	Key_init();
	
	while(font_init()) 			//检查字库
	{;}  
	while(NRF24L01_Check())
	{
		LCD_ShowString(30,130,200,16,16,"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	old_id_read();
		NRF24L01_RX_Mode();	
	LCD_Clear(WHITE);	
  	while(1)
	{

		use_control();
	}	 
} 






