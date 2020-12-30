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

int dh[6];                   //温湿度数据
int dt[7]={1,1,1,1,0,0,0};  //  电机、粉尘监测、下雨监测、火源检测  刷卡登录者（3个）（1正常   0异常）
int ID[12]={0,0,0,0,0,0,0,0,0,0,0,0};     
u8 temperature;  	    
u8 humidity;  	
 extern u16 adcx;
 extern u16 adcx2;
extern unsigned char SN[4]; //卡号
void Usart_control(void);
u8 user;
 u8 door;
unsigned char CT[2];//卡类型
unsigned char SN[4]; //卡号
unsigned char RFID[16];			//存放RFID 
unsigned char RFID1[16]={0x01,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
int main(void)
{				 
	
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	InitRc522();
	Adc_Init();
	Adc2_Init();
	LED_Init();
	 while(DHT11_Init())	//DHT11初始化	
	{;}	
		PWM_Init(200,7199);      //舵机控制需要20ms的脉冲即50HZ    50=72 000 000/psc*arr 
	TIM3_Int_Init(9999,7199);//10Khz的计数频率，100ms
	JG=1;                //激光灯常亮
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
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				for(t=0;t<2;t++)
			{
				USART1->DR=48+dh[t];   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
			}
				USART1->DR='c';   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				for(t=3;t<5;t++)
			{
				
				USART1->DR=48+dh[t];   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
			}
				delay_ms(50);
	 //电机工作
								USART1->DR='b';   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				if(dt[0]==1)
				{
				printf("不工作");
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				delay_ms(50);
				}
				else
				{
				printf("工作");
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				delay_ms(50);
				}
				delay_ms(50);
				//粉尘
												USART1->DR='d';   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				if(dt[1]==1)
				{
				printf("正常");
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				delay_ms(50);
				}
				else
				{
				printf("粉尘过大");
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				delay_ms(50);
				}
				delay_ms(50);
				//yud
												USART1->DR='e';   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				if(dt[2]==1)
				{
				printf("无雨");
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				delay_ms(50);
				}
				else
				{
				printf("有雨");
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				delay_ms(50);
				}
				delay_ms(50);
				
								//火源
												USART1->DR='f';   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				if(dt[3]==1)
				{
				printf("正常");
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				delay_ms(50);
				}
				else
				{
				printf("火警警告");
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				delay_ms(50);
				}
				if(user==1)
				{
												USART1->DR='g';   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				for(t=0;t<12;t++)
			{
				USART1->DR=48+ID[t];   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
			}
			user=21;
				}
						else if(user==2)
				{
												USART1->DR='h';   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				for(t=0;t<12;t++)
			{
				USART1->DR=48+ID[t];   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
			}
			user=22;
				}
						else if(user==3)
				{
												USART1->DR='i';   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
				for(t=0;t<12;t++)
			{
				USART1->DR=48+ID[t];   
				while((USART1->SR&0X40)==0) { ; }//等待发送结束
			}
			user=23;
				}




	}	




