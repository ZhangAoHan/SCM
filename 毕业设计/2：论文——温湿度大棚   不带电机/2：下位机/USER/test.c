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
unsigned char CT[2];//������
unsigned char SN[4]; //����
unsigned char RFID[16];			//���RFID 
unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};

int main(void)
{		
			 

 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
 	NRF24L01_Init();    	//��ʼ��NRF24L01  	
//	Adc_Init();		  		//ADC��ʼ��		
//	Adc1_Init();
//	Adc2_Init();
//	PWM_Init(200,7199);      //���������Ҫ20ms�����弴50HZ    50=72 000 000/psc*arr 
	LED_Init();
	InitRc522();
	TIM1_PWM_Init(9999,0);
 	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
	{;}		

//	 while(DHT11_Init())	//DHT11��ʼ��	
//	{;}	
		
	TIM3_Int_Init(999,7199);//10Khz�ļ���Ƶ�ʣ�100ms
while(1)
{
	user_control();
	
}
	
}



















