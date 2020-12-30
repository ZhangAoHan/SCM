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
unsigned char SN[4]; //����
u8 page=0;
u16 t1;
u16 t2;
u16 t3;
u16 time1;
u16 time2;
u16 time3;
int main(void)
{				 

	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	LED_Init();
	NRF24L01_Init();    		//��ʼ��NRF24L01 

	while(font_init()) 			//����ֿ�
	{
	LCD_ShowString(30,50,200,16,16,"TFT Error");
	}  
		Show_Str(6,50,96,24,"�ֿ�����",24,0);
		while(NRF24L01_Check())
	{
		LCD_ShowString(30,130,200,16,16,"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	LCD_ShowString(30,130,200,16,16,"NRF24L01 OK"); 	 
		
		LCD_Clear(WHITE);
	PWM_Init(10000,0);      //���������Ҫ20ms�����弴50HZ    50=72 000 000/psc*arr 
	TIM3_Int_Init(9999,7199);//10Khz�ļ���Ƶ�ʣ�100ms
		delay_ms(100);
	NRF24L01_RX_Mode();		
	
  	while(1)
	{

		user_control();
	}	 
} 






