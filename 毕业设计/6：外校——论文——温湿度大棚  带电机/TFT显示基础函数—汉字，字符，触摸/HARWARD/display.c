#include "display.h"
#include "text.h"
#include "lcd.h"
#include "date.h"
#include "delay.h"	
#include "control.h"
#include "touch.h"  
#include "w25q128.h" 
#include "at24c02.h"   

extern u8 temperature;  	    
extern u8 humidity;  	
extern u16 adcx;	
extern u8 temperature2;  	    
extern u8 humidity2;  	
extern u16 adcx2;
extern u16 adcx3;
extern u16 adcx4;
extern u16 adcx0;
u8 settle;
extern u8 t1,t2,t3,t4,t5;
extern u8 tt1,tt2,tt3,tt4,tt5;
extern u8 h1,h2,h3,h4,h5;
extern u8 hh1,hh2,hh3,hh4,hh5;
void LCD_Init_Display(void)
{

	POINT_COLOR=BLUE;
	Show_Str(24,5,192,48,"大棚蔬菜环境监测系统的设计与实现",24,0);
	POINT_COLOR=RED;
	Show_Str(5,60,120,24,"TFT屏字库正常",24,0);
	Show_Str(5,85,120,24,"TFT屏触摸功能正常",24,0);
	Show_Str(5,110,120,24,"DHT11初始化正常",24,0);
	Show_Str(5,135,120,24,"光敏初始化完成",24,0);
	Show_Str(5,160,120,24,"继电器初始化完成",24,0);
	
	delay_ms(10); 
}


void Use1_init_diaplsy(void)      //page=0
{
	POINT_COLOR=BLUE;
	Show_Str(24,5,192,48,"大棚蔬菜环境监测系统的设计与实现",24,0);
	POINT_COLOR=RED;
	LCD_DrawRectangle(5,59,239,210);
	LCD_DrawRectangle(4,58,240,211);
	POINT_COLOR=BLACK;
	Show_Str(6,60,120,24,"环境光强：",24,0);
	Show_Str(6,85,120,24,"环境温度：",24,0);
	Show_Str(6,110,120,24,"环境湿度：",24,0);
	Show_Str(6,135,120,24,"气体浓度：",24,0);
	Show_Str(6,160,120,24,"下雨检测",24,0);
	Show_Str(6,185,120,24,"土壤温湿度",24,0);
	POINT_COLOR=BLUE;
	Show_Str(48,230,144,24,"制作人：武艳",24,0);
	POINT_COLOR=RED;
	Show_Str(6,290,120,24,"更换检测组",24,0);
	Show_Str(6,260,120,24,"数据信息",24,0);
}

void Use1_date_display(void)             //page=0
{
	date_read();
	
	if(settle==0)
	{
		Show_Str(130,64,48,24,"A组",24,0);
		Show_Str(130,89,48,24,"A组",24,0);
		Show_Str(130,114,48,24,"A组",24,0);
		LCD_ShowNum(170,89,temperature,4,16);
		LCD_ShowNum(170,114,humidity,4,16);
		LCD_ShowNum(170,64,adcx,4,16);
		if(adcx-2000>0) LED_PWM=(adcx-2000)*2;
		else LED_PWM=0;
	}
		if(settle==1)
	{
		Show_Str(130,64,36,24,"B组",24,0);
		Show_Str(130,89,36,24,"B组",24,0);
		Show_Str(130,114,36,24,"B组",24,0);
		LCD_ShowNum(170,89,temperature2,4,16);
		LCD_ShowNum(170,114,humidity2,4,16);
		LCD_ShowNum(170,64,adcx2,4,16);
		if(adcx2-2000>0) LED_PWM=(adcx2-2000)*2;
		else LED_PWM=0;
	}

	LCD_ShowNum(170,164,adcx4,4,16);
	LCD_ShowNum(170,189,adcx3,4,16);
	LCD_ShowNum(150,139,adcx0,5,16);
	if(adcx0>300)
	{
		FS=0;
		BEEP=0;
		LED_YELLOW=0;
		LED_BLUE=0;
		LED_RED=1;
	}
	else 
	{
		FS=1;
		BEEP=1;
		LED_YELLOW=1;
		LED_BLUE=0;
		LED_RED=0;
	}
}

void date_save(void)
{
	t1=t2;
	t2=t3;
	t3=t4;
	t4=t5;
	tt1=tt2;
	tt2=tt3;
	tt3=tt4;
	tt4=tt5;
	h1=h2;
	h2=h3;
	h3=h4;
	h4=h5;
	hh1=hh2;
	hh2=hh3;
	hh3=hh4;
	hh4=hh5;
	
	t5=temperature;
	tt5=temperature2;
	h5=humidity;
	hh5=humidity2;	
}

void date_init_display(u8 ch)               //page==1
{
	POINT_COLOR=BLUE;
	Show_Str(24,5,192,48,"大棚蔬菜环境监测系统的设计与实现",24,0);
	POINT_COLOR=RED;
	LCD_DrawRectangle(5,59,239,240);
	LCD_DrawRectangle(4,58,240,241);
	if(ch==0)
	{
	POINT_COLOR=BLUE;
	Show_Str(10,65,132,24,"温度",24,0);
	POINT_COLOR=BLACK;
	Show_Str(135,90,48,24,"A组",24,0);
	Show_Str(187,90,48,24,"B组",24,0);
	Show_Str(6,115,120,24,"第一次温度",24,0);
	Show_Str(6,140,120,24,"第二次温度",24,0);
	Show_Str(6,165,120,24,"第三次温度",24,0);
	Show_Str(6,190,120,24,"第四次温度",24,0);
	Show_Str(6,215,120,24,"第五次温度",24,0);
	POINT_COLOR=RED;
	Show_Str(30,245,96,24,"湿度数据",24,0);
	Show_Str(180,245,48,24,"返回",24,0);
	}
	else if(ch==1)
	{
	POINT_COLOR=BLUE;
	Show_Str(10,65,132,24,"湿度",24,0);
	POINT_COLOR=BLACK;
	Show_Str(135,90,48,24,"A组",24,0);
	Show_Str(187,90,48,24,"B组",24,0);
	Show_Str(6,115,120,24,"第一次湿度",24,0);
	Show_Str(6,140,120,24,"第二次湿度",24,0);
	Show_Str(6,165,120,24,"第三次湿度",24,0);
	Show_Str(6,190,120,24,"第四次湿度",24,0);
	Show_Str(6,215,120,24,"第五次湿度",24,0);
	POINT_COLOR=RED;
	Show_Str(30,245,96,24,"温度数据",24,0);
	Show_Str(180,245,48,24,"返回",24,0);
	Show_Str(30,270,144,24,"湿度数据图表",24,0);
	}
}

void date_display(u8 ch)
{
	POINT_COLOR=BLACK;
	if(ch==0)
	{
				LCD_ShowNum(135,119,t1,3,16);
		LCD_ShowNum(187,119,tt1,3,16);
				LCD_ShowNum(135,144,t2,3,16);
		LCD_ShowNum(187,144,tt2,3,16);
				LCD_ShowNum(135,169,t3,3,16);
		LCD_ShowNum(187,169,tt3,3,16);
				LCD_ShowNum(135,194,t4,3,16);
		LCD_ShowNum(187,194,tt4,3,16);
				LCD_ShowNum(135,219,t5,3,16);
		LCD_ShowNum(187,219,tt5,3,16);
	}
	else if(ch==1)
	{
				LCD_ShowNum(135,119,h1,3,16);
		LCD_ShowNum(187,119,hh1,3,16);
				LCD_ShowNum(135,144,h2,3,16);
		LCD_ShowNum(187,144,hh3,3,16);
				LCD_ShowNum(135,169,h3,3,16);
		LCD_ShowNum(187,169,hh3,3,16);
				LCD_ShowNum(135,194,h4,3,16);
		LCD_ShowNum(187,194,hh4,3,16);
				LCD_ShowNum(135,219,h5,3,16);
		LCD_ShowNum(187,219,hh5,3,16);
	}
}
void Block_init_display(void)              //page=3
{
	POINT_COLOR=BLUE;
	Show_Str(24,5,192,48,"大棚蔬菜环境监测系统的设计与实现",24,0);
	POINT_COLOR=BLACK;
	Show_Str(8,80,32,16,"A组",16,0);
	Show_Str(8,100,32,16,"湿度",16,0);
	Show_Str(195,155,32,16,"时间",16,0);
	Show_Str(8,200,32,16,"B组",16,0);
	Show_Str(8,220,32,16,"湿度",16,0);
	Show_Str(190,275,32,16,"时间",16,0);

	POINT_COLOR=RED;
	Show_Str(190,295,48,24,"返回",24,0);
	LCD_DrawLine(45,80,45,150);
	LCD_DrawLine(44,80,44,150);
	LCD_DrawLine(44,151,195,151);
	LCD_DrawLine(44,152,195,152);
	
	LCD_DrawLine(43,83,45,78);
	LCD_DrawLine(47,83,45,78);
	LCD_DrawLine(192,149,197,151);
	LCD_DrawLine(192,154,197,151);
	
	LCD_DrawLine(45,200,45,270);
	LCD_DrawLine(44,200,44,270);
	LCD_DrawLine(44,271,195,271);
	LCD_DrawLine(44,272,195,272);
	
	LCD_DrawLine(43,203,45,198);
	LCD_DrawLine(47,203,45,198);
	LCD_DrawLine(192,269,197,271);
	LCD_DrawLine(192,274,197,271);
}

void Block_date_display(void)                   //page==3
{
	POINT_COLOR=BLUE;
	if(145-h1/3<80) h1=195;
	if(145-h2/3<80) h2=195;
	if(145-h3/3<80) h3=195;
	if(145-h4/3<80) h4=195;
	if(145-h5/3<80) h5=195;
	LCD_DrawLine(50,145-h1/3,70,145-h2/3);
	LCD_DrawLine(70,145-h2/3,90,145-h3/3);
	LCD_DrawLine(90,145-h3/3,120,145-h4/3);
	LCD_DrawLine(120,145-h4/3,150,145-h5/3);
	if(265-hh1/3<200) hh1=195;
	if(265-hh2/3<200) hh2=195;
	if(265-hh3/3<200) hh3=195;
	if(265-hh4/3<200) hh4=195;
	if(265-hh5/3<200) hh5=195;
	LCD_DrawLine(50,265-hh1/3,70,265-hh2/3);
	LCD_DrawLine(70,265-hh2/3,90,265-hh3/3);
	LCD_DrawLine(90,265-hh3/3,120,265-hh4/3);
	LCD_DrawLine(120,265-hh4/3,150,265-hh5/3);
}
