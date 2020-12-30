#include "display.h"

u8 group;         //

void init_display(void)
{
	while(font_init()) 			//检查字库
	{;}  
	POINT_COLOR=BLUE;
	Show_Str(48,5,144,48,"大棚蔬菜生长环境检测系统",24,0);
	POINT_COLOR=RED;
	Show_Str(10,100,120,24,"TFT屏字库正常",24,0);
	Show_Str(10,100,120,24,"TFT屏触摸功能正常",24,0);
	while(DHT11_Init())	//DHT11初始化	
	{;}
	Show_Str(10,100,120,24,"DHT11功能正常",24,0);
	delay_ms(500); 
}

void use_1_init_display(void)      //page=0
{
	POINT_COLOR=BLUE;
	Show_Str(48,5,144,48,"大棚蔬菜生长环境检测系统",24,0);
	POINT_COLOR=BLACK;
	Show_Str(5,60,120,24,"环境光强：",24,0);
	Show_Str(5,85,120,24,"环境温度：",24,0);
	Show_Str(5,110,120,24,"环境湿度：",24,0);
	Show_Str(5,135,144,24,"调节灯：",24,0);
}
void use_1_data_display(void)  
{
	date_read();
	LCD_ShowNum(125,64,adcx,4,16);
	if(group==0x0)            //第一组数据
	{
		Show_Str(125,85,48,24,"A组",24,0);
		LCD_ShowNum(175,89,temperature,4,16);
		Show_Str(125,110,48,24,"A组",24,0);
		LCD_ShowNum(175,114,humidity,4,16);
	}
	else if(group==0x1)      //第一组数据
	{
		Show_Str(125,85,48,24,"B组",24,0);
		LCD_ShowNum(175,89,temperature,4,16);
		Show_Str(125,110,48,24,"B组",24,0);
		LCD_ShowNum(175,114,humidity,4,16);
	}	
}














