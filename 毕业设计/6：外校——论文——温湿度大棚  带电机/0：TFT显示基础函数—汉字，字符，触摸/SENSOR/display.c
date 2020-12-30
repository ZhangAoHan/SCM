#include "display.h"

u8 group;         //

void init_display(void)
{
	while(font_init()) 			//����ֿ�
	{;}  
	POINT_COLOR=BLUE;
	Show_Str(48,5,144,48,"�����߲������������ϵͳ",24,0);
	POINT_COLOR=RED;
	Show_Str(10,100,120,24,"TFT���ֿ�����",24,0);
	Show_Str(10,100,120,24,"TFT��������������",24,0);
	while(DHT11_Init())	//DHT11��ʼ��	
	{;}
	Show_Str(10,100,120,24,"DHT11��������",24,0);
	delay_ms(500); 
}

void use_1_init_display(void)      //page=0
{
	POINT_COLOR=BLUE;
	Show_Str(48,5,144,48,"�����߲������������ϵͳ",24,0);
	POINT_COLOR=BLACK;
	Show_Str(5,60,120,24,"������ǿ��",24,0);
	Show_Str(5,85,120,24,"�����¶ȣ�",24,0);
	Show_Str(5,110,120,24,"����ʪ�ȣ�",24,0);
	Show_Str(5,135,144,24,"���ڵƣ�",24,0);
}
void use_1_data_display(void)  
{
	date_read();
	LCD_ShowNum(125,64,adcx,4,16);
	if(group==0x0)            //��һ������
	{
		Show_Str(125,85,48,24,"A��",24,0);
		LCD_ShowNum(175,89,temperature,4,16);
		Show_Str(125,110,48,24,"A��",24,0);
		LCD_ShowNum(175,114,humidity,4,16);
	}
	else if(group==0x1)      //��һ������
	{
		Show_Str(125,85,48,24,"B��",24,0);
		LCD_ShowNum(175,89,temperature,4,16);
		Show_Str(125,110,48,24,"B��",24,0);
		LCD_ShowNum(175,114,humidity,4,16);
	}	
}














