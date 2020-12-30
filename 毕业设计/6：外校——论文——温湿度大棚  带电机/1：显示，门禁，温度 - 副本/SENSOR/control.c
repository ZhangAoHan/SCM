#include "control.h"
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"
#include "ds18b20.h"   
#include "ds18b202.h"
#include "rc522.h"
#include "timer.h"
#include "adc.h"
#include "led.h"
#include "delay.h"	
#include "memory.h" 

u16 adcx1;    //����
u16 adcx2;    //Һλ
u16 LL;     //ˮ����
extern u16 SL;
extern u8 nn;
extern u8 page;
unsigned char CT[2];//������
unsigned char SN[4]; //����
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};

void init_display(void)  //��ʼ����ʾ  ���Գ�ˮ��DS18B20�����ӳټ��
{
	while(font_init()) 			//����ֿ�
	{;}  
	POINT_COLOR=BLUE;
	Show_Str(24,5,240,24,"����ˮ����ϵͳ",24,0);
	POINT_COLOR=BLACK;
	Show_Str(48,35,240,24,"���ϵͳ",24,0);
	delay_ms(3000);
	LCD_Fill(5,65,240,24,WHITE);
	POINT_COLOR=BLUE;
	Show_Str(24,5,240,24,"����ˮ����ϵͳ",24,0);
	POINT_COLOR=BLACK;
	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	while(DS18B202_Init())	//DS18B20��ʼ��	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B202 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	POINT_COLOR=BLACK;
	
	Show_Str(5,65,240,24,"TFT��������������",24,0);
	Show_Str(5,95,240,24,"��ˮ��DS18B20����",24,0);
	Show_Str(5,125,240,24,"��ˮ��DS18B20����",24,0);
	Show_Str(5,155,240,24,"ˮ�ÿ��Ƶ�·����",24,0);
	Show_Str(5,185,240,24,"��������������",24,0);
	Show_Str(5,215,240,24,"RFID��д����������",24,0);
	Show_Str(5,245,240,24,"����������������",24,0);
	Show_Str(5,245,240,24,"�źŵƹ�������",24,0);
	delay_ms(5000);
	LCD_Clear(WHITE);	
}

void main_display(void)              //��ҳ��  page=0
{
	date_read();
	POINT_COLOR=BLUE;
	Show_Str(24,5,240,24,"����ˮ����ϵͳ",24,0);
	LCD_DrawRectangle(5,30,235,214);
	LCD_DrawRectangle(4,29,236,215);
	POINT_COLOR=RED;
	Show_Str(36,35,168,24,"��ˮ���¶�����",24,0);
	Show_Str(36,65,168,24,"��ˮ���¶�����",24,0);
	POINT_COLOR=BLACK;
	Show_Str(10,95,144,24,"ˮ����������",24,0);
	LCD_ShowNum(165,99,LL,4,16);
	LCD_ShowString(200,99,39,16,16,"L/H");
	Show_Str(10,125,144,24,"��������Ũ��",24,0);
	LCD_ShowNum(165,129,adcx1,4,16);
	LCD_ShowString(200,129,39,16,16,"Ppm");
//	Show_Str(10,155,108,24,"Һ�������",24,0);
	Show_Str(10,155,108,24,"ˮ�������",24,0);
	POINT_COLOR=RED;
	Show_Str(10,185,96,24,"ˮ�ÿ���",24,0);
		POINT_COLOR=BLACK;
	if(tim==0) 
	{
		Show_Str(125,155,96,24,"ˮ�ùر�",24,0);
		
	}
	else if(tim==1) 
	{
		Show_Str(125,155,96,24,"ˮ�ÿ���",24,0);
		
	}
	POINT_COLOR=BLUE;
	Show_Str(10,245,240,24,"������ID��Ϣ��",24,0);
	POINT_COLOR=BLACK;
	LCD_ShowNum(10,270,SN[0],3,16);
	LCD_ShowNum(58,270,SN[1],3,16);	
	LCD_ShowNum(106,270,SN[2],3,16);	
	LCD_ShowNum(154,270,SN[3],3,16);
	Show_Str(10,295,96,24,"�˳���¼",24,0);
}

void date_read(void)
{
		adcx1=Get_Adc_Average(ADC_CH1,10);
//		adcx2=Get_Adc_Average(ADC_CH2,10);
		LL=(SL*40)/16;
		
}
void RFID_read(void)
{
		unsigned char status;
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
				page=0;   //�����¼�ɹ�  ������ҳ��
			 		LCD_Clear(WHITE);
					delay_ms(10);

		  } 
}
void DL_display(void)   //page=1
{
	POINT_COLOR=BLUE;
	Show_Str(60,100,240,24,"��ˢ����¼",24,0);
	POINT_COLOR=BLACK;
	RFID_read();
	LED_RED=0;
	LED_YELLOW=0;
	LED_GREEN=0;
}
void use_touch(void)
{
		tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(page==0)   //��ҳ��
			{
				if(tp_dev.x[0]>36&&tp_dev.x[0]<204&&tp_dev.y[0]>35&&tp_dev.y[0]<59)
				{
					page=10;
					LCD_Clear(WHITE);
					delay_ms(10);
				}
				else if(tp_dev.x[0]>36&&tp_dev.x[0]<204&&tp_dev.y[0]>65&&tp_dev.y[0]<89)
				{
					page=11;
					LCD_Clear(WHITE);
					delay_ms(10);
				}
				else if(tp_dev.x[0]>10&&tp_dev.x[0]<110&&tp_dev.y[0]>294&&tp_dev.y[0]<320)
				{
					page=1;
					LCD_Clear(WHITE);
					delay_ms(10);
				}
				else if(tp_dev.x[0]>10&&tp_dev.x[0]<110&&tp_dev.y[0]>185&&tp_dev.y[0]<210)
				{
					SB=!SB;
					tim=!tim;
					nn=!nn;
					delay_ms(10);
				}
			}
			else  if(page==10)
			{
				if(tp_dev.x[0]>185&&tp_dev.x[0]<240&&tp_dev.y[0]>213&&tp_dev.y[0]<240)
				{
					page=0;
					LCD_Clear(WHITE);
					delay_ms(10);
				}
				if(tp_dev.x[0]>10&&tp_dev.x[0]<110&&tp_dev.y[0]>213&&tp_dev.y[0]<240)
				{
					tempdate1=date1=tempdate2=date2=tempdate3=date3=tempdate4=date4=tempdate5=date5=0;
					delay_ms(10);
				}
			}
			else  if(page==11)
			{
				if(tp_dev.x[0]>185&&tp_dev.x[0]<240&&tp_dev.y[0]>213&&tp_dev.y[0]<240)
				{
					page=0;
					LCD_Clear(WHITE);
					delay_ms(10);
				}
				if(tp_dev.x[0]>10&&tp_dev.x[0]<110&&tp_dev.y[0]>213&&tp_dev.y[0]<240)
				{
					tempoutdate1=outdate1=tempoutdate2=outdate2=tempoutdate3=outdate3=tempoutdate4=outdate4=tempoutdate5=outdate5=0;
					delay_ms(10);
				}
			}
		}
	}
}

void control(void)
{
	use_touch();
	if(page==0)
	{
		main_display();
		LED_YELLOW=1;
		LED_GREEN=0;
	}
	else if(page==10)
	{
		Temp_display(30,0);
		LED_GREEN=1;
		LED_YELLOW=0;
	}
	else if(page==11)
	{
		Temp_display(30,1);
		LED_GREEN=1;
		LED_YELLOW=0;
	}
	else if(page==1)
	{
		DL_display();
		tim=0;
	}
}
