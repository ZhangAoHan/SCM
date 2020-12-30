#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"
#include "ds18b20.h"   
#include "rc522.h"
#include "timer.h"
#include "adc.h"
#include "led.h"
#include "key.h"
#include "control.h"


u8 page=0;
unsigned char card_1[4];
unsigned char card_2[4];
unsigned char card_3[4];
u8 n=0;    //选择的车位
u16 t1=0,t2=0,t3=0;    //使用时间
u8 use1=0,use2=0,use3=0; 
u8 door;
/*全局变量*/

//unsigned char RFID[16];			//存放RFID 
//unsigned char lxl_bit=0;
//unsigned char total=0;
//unsigned char lxl[4]={6,109,250,186};
//unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};

int main(void)
{		

//	
	
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	PWM_Init(200,7199);      //舵机控制需要20ms的脉冲即50HZ    50=72 000 000/psc*arr 
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	InitRc522();
	Adc_Init();		  		//ADC初始化	    
	LED_Init();	
	KEY_Init(); 
	LCD_init_display();
	TIM3_Int_Init(9999,7199);//10Khz的计数频率，100ms
 	while(1)
	{	
				control();
	

			  
	}

	}	 







