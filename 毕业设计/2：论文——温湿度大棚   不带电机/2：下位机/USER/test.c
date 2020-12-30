#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "24l01.h" 
#include "control.h"
#include "dht11.h"
#include "adc.h"
#include "timer.h"
#include "led.h"
#include "rc522.h"
u8 tmp_buf[33]; 
	u8 temperature;  	    
	u8 humidity; 
	u16 adcx;
	u16 adcx1;
	u16 adcx2;
	u8 set=0;
	u8 settle=0;
	u8 door;
unsigned char CT[2];//卡类型
unsigned char SN[4]; //卡号
unsigned char RFID[16];			//存放RFID 
unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};

int main(void)
{		
			 

 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
 	NRF24L01_Init();    	//初始化NRF24L01  	
//	Adc_Init();		  		//ADC初始化		
//	Adc1_Init();
//	Adc2_Init();
//	PWM_Init(200,7199);      //舵机控制需要20ms的脉冲即50HZ    50=72 000 000/psc*arr 
	LED_Init();
	InitRc522();
	TIM1_PWM_Init(9999,0);
 	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{;}		

//	 while(DHT11_Init())	//DHT11初始化	
//	{;}	
		
	TIM3_Int_Init(999,7199);//10Khz的计数频率，100ms
while(1)
{
	user_control();
	
}
	
}



















