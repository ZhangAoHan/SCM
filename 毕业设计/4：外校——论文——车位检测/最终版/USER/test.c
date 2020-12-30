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
u8 n=0;    //ѡ��ĳ�λ
u16 t1=0,t2=0,t3=0;    //ʹ��ʱ��
u8 use1=0,use2=0,use3=0; 
u8 door;
/*ȫ�ֱ���*/

//unsigned char RFID[16];			//���RFID 
//unsigned char lxl_bit=0;
//unsigned char total=0;
//unsigned char lxl[4]={6,109,250,186};
//unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};

int main(void)
{		

//	
	
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	PWM_Init(200,7199);      //���������Ҫ20ms�����弴50HZ    50=72 000 000/psc*arr 
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	InitRc522();
	Adc_Init();		  		//ADC��ʼ��	    
	LED_Init();	
	KEY_Init(); 
	LCD_init_display();
	TIM3_Int_Init(9999,7199);//10Khz�ļ���Ƶ�ʣ�100ms
 	while(1)
	{	
				control();
	

			  
	}

	}	 







