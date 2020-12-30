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

/*全局变量*/
unsigned char CT[2];//卡类型
unsigned char SN[4]; //卡号
//unsigned char RFID[16];			//存放RFID 
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
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	PWM_Init(200,7199);      //舵机控制需要20ms的脉冲即50HZ    50=72 000 000/psc*arr 
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	while(font_init()) 			//检查字库
	{;}  
	InitRc522();
	Adc_Init();		  		//ADC初始化	    
	Show_Str(150,200,48,24,"校准",24,0);
	LED_Init();	
	KEY_Init(); 
	while(DS18B20_Init())	//DS18B20初始化	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}
//	Show_Str(5,5,132,24,"第一次数据：",24,0);
//	Show_Str(5,35,132,24,"第二次数据：",24,0);
//	Show_Str(5,65,108,24,"温度数据：",24,0);
//		LCD_DrawRectangle(10,10,150,80);
//		LCD_ShowString(11,11,80,16,16,"right");
//		LCD_DrawRectangle(10,100,150,170);
//		LCD_ShowString(11,101,64,16,16,"left");
//		Show_Str(150,200,48,24,"校准",24,0);
		
 	while(1)
	{	
		status = PcdRequest(PICC_REQALL,CT);/*尋卡*/
		if(status==MI_OK)//尋卡成功
		{
			 status=MI_ERR;
			 status = PcdAnticoll(SN);/*防冲撞*/
		}	
		if(status==MI_OK)
		{
			status=MI_ERR;
			status =PcdSelect(SN);
		}

		if(status==MI_OK)//選卡成功
		{
			 status=MI_ERR;
			 status =PcdAuthState(0x61,0x06,KEY,SN);
		 }
	
		 if(status==MI_OK)//驗證成功
		 {
			  status=MI_ERR;
			  for(t=0;t<4;t++)
			  {
					LCD_ShowNum(0,116+t*16,SN[t],3,16);
			  }	  
		  }
	 if(status==MI_OK)//驗證成功
		 {
			status=MI_ERR;
			LCD_ShowNum(0,116+t*16,SN[t],3,16);

			  }	 
//	PWM=5;    //中值
//	delay_ms(500);
//	 PWM=15;    //偏25°左右
//	delay_ms(500);
//	temp_memory();
		adcx=Get_Adc_Average(ADC_CH1,10);
		LCD_ShowxNum(126,130,adcx,4,16,0);//显示ADC的值
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







