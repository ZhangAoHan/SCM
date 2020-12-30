#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"
#include "ds18b20.h"   
#include "memory.h" 
#include "rc522.h"
#include "timer.h"
#include "adc.h"
#include "led.h"
#include "in.h"

/*ȫ�ֱ���*/
unsigned char CT[2];//������
unsigned char SN[4]; //����
//unsigned char RFID[16];			//���RFID 
//unsigned char lxl_bit=0;
//unsigned char total=0;
//unsigned char lxl[4]={6,109,250,186};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
//unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};

int main(void)
{		
	unsigned char status;
	u8 t;
	u16 adcx;
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	PWM_Init(200,7199);      //���������Ҫ20ms�����弴50HZ    50=72 000 000/psc*arr 
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	while(font_init()) 			//����ֿ�
	{;}  
	InitRc522();
	Adc_Init();		  		//ADC��ʼ��	    
	Show_Str(150,200,48,24,"У׼",24,0);
	LED_Init();	
	KEY_Init(); 
	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}
//	Show_Str(5,5,132,24,"��һ�����ݣ�",24,0);
//	Show_Str(5,35,132,24,"�ڶ������ݣ�",24,0);
//	Show_Str(5,65,108,24,"�¶����ݣ�",24,0);
//		LCD_DrawRectangle(10,10,150,80);
//		LCD_ShowString(11,11,80,16,16,"right");
//		LCD_DrawRectangle(10,100,150,170);
//		LCD_ShowString(11,101,64,16,16,"left");
//		Show_Str(150,200,48,24,"У׼",24,0);
		
 	while(1)
	{	
		status = PcdRequest(PICC_REQALL,CT);/*����*/
		if(status==MI_OK)//�����ɹ�
		{
			 status=MI_ERR;
			 status = PcdAnticoll(SN);/*����ײ*/
		}	
		if(status==MI_OK)
		{
			status=MI_ERR;
			status =PcdSelect(SN);
		}

		if(status==MI_OK)//�x���ɹ�
		{
			 status=MI_ERR;
			 status =PcdAuthState(0x61,0x06,KEY,SN);
		 }
	
		 if(status==MI_OK)//��C�ɹ�
		 {
			  status=MI_ERR;
			  for(t=0;t<4;t++)
			  {
					LCD_ShowNum(0,116+t*16,SN[t],3,16);
			  }	  
		  }
	 if(status==MI_OK)//��C�ɹ�
		 {
			status=MI_ERR;
			LCD_ShowNum(0,116+t*16,SN[t],3,16);

			  }	 
//	PWM=5;    //��ֵ
//	delay_ms(500);
//	 PWM=15;    //ƫ25������
//	delay_ms(500);
//	temp_memory();
		adcx=Get_Adc_Average(ADC_CH1,10);
		LCD_ShowxNum(126,130,adcx,4,16,0);//��ʾADC��ֵ
			  if(HY1==1)
			  {
			  		LED_RED=1;
					LED_YELLOW=1;	
					LED_GREEN=1;
			  }
			  			  if(HY1==0)
			  {
			  		LED_RED=0;
					LED_YELLOW=0;	
					LED_GREEN=0;
			  }
	
			  
	}

	}	 







