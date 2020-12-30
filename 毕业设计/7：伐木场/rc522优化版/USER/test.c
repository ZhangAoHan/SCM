#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"	
#include "rc522.h"
#include "dht11.h"
#include "adc.h"
#include "display.h"

int dh[6];                   //��ʪ������
int dt[7]={1,1,1,1,0,0,0};  //  ������۳���⡢�����⡢��Դ���  ˢ����¼�ߣ�3������1����   0�쳣��
int ID[12]={0,0,0,0,0,0,0,0,0,0,0,0};     
u8 temperature;  	    
u8 humidity;  	
 extern u16 adcx;
 extern u16 adcx2;
extern unsigned char SN[4]; //����
void Usart_control(void);
u8 user;
 u8 door;
unsigned char CT[2];//������
unsigned char SN[4]; //����
unsigned char RFID[16];			//���RFID 
unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
int main(void)
{				 
	
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	InitRc522();
	Adc_Init();
	Adc2_Init();
	LED_Init();
	 while(DHT11_Init())	//DHT11��ʼ��	
	{;}	
		PWM_Init(200,7199);      //���������Ҫ20ms�����弴50HZ    50=72 000 000/psc*arr 
	TIM3_Int_Init(9999,7199);//10Khz�ļ���Ƶ�ʣ�100ms
	JG=1;                //����Ƴ���
  	while(1)
	{
		control();
		Usart_control();
		
	}
 
} 


void Usart_control(void)
{
		u8 t;
		DHT11_Read_Data(&temperature,&humidity);

		dh[0]=(temperature/10)%10;
		dh[1]=temperature%10;
		
		dh[3]=(humidity/10)%10;
		dh[4]=humidity%10;
				USART1->DR='a';   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				for(t=0;t<2;t++)
			{
				USART1->DR=48+dh[t];   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
			}
				USART1->DR='c';   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				for(t=3;t<5;t++)
			{
				
				USART1->DR=48+dh[t];   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
			}
				delay_ms(50);
	 //�������
								USART1->DR='b';   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				if(dt[0]==1)
				{
				printf("������");
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				delay_ms(50);
				}
				else
				{
				printf("����");
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				delay_ms(50);
				}
				delay_ms(50);
				//�۳�
												USART1->DR='d';   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				if(dt[1]==1)
				{
				printf("����");
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				delay_ms(50);
				}
				else
				{
				printf("�۳�����");
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				delay_ms(50);
				}
				delay_ms(50);
				//yud
												USART1->DR='e';   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				if(dt[2]==1)
				{
				printf("����");
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				delay_ms(50);
				}
				else
				{
				printf("����");
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				delay_ms(50);
				}
				delay_ms(50);
				
								//��Դ
												USART1->DR='f';   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				if(dt[3]==1)
				{
				printf("����");
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				delay_ms(50);
				}
				else
				{
				printf("�𾯾���");
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				delay_ms(50);
				}
				if(user==1)
				{
												USART1->DR='g';   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				for(t=0;t<12;t++)
			{
				USART1->DR=48+ID[t];   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
			}
			user=21;
				}
						else if(user==2)
				{
												USART1->DR='h';   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				for(t=0;t<12;t++)
			{
				USART1->DR=48+ID[t];   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
			}
			user=22;
				}
						else if(user==3)
				{
												USART1->DR='i';   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
				for(t=0;t<12;t++)
			{
				USART1->DR=48+ID[t];   
				while((USART1->SR&0X40)==0) { ; }//�ȴ����ͽ���
			}
			user=23;
				}




	}	




