#include "memory.h" 
#include "delay.h"
#include "at24c02.h" 
#include "ds18b20.h"
#include "math.h"
#include "lcd.h"
#include "text.h"
#include "ds18b202.h"
extern u8 tempdate1,date1,tempdate2,date2,tempdate3,date3,tempdate4,date4,tempdate5,date5;
extern u8 tempoutdate1,outdate1,tempoutdate2,outdate2,tempoutdate3,outdate3,tempoutdate4,outdate4,tempoutdate5,outdate5;

short temperature; 
short temperature1; 
void readin_temp(void)
{

	temperature=DS18B20_Get_Temp();	
	if(temperature<0)
	{
		temperature=-temperature;					//转为正数
	}
}
void readout_temp(void)
{

	temperature1=DS18B202_Get_Temp();	
	if(temperature1<0)
	{
		temperature1=-temperature1;					//转为正数
	}
	
}
void tempin_memory(void)         //每一秒读取一次温度数据
{

	readin_temp();

			tempdate1=tempdate2;
	tempdate2=tempdate3;
	tempdate3=tempdate4;
	tempdate4=tempdate5;
	date1=date2;
	date2=date3;
	date3=date4;
	date4=date5;
	
	tempdate5=temperature/20;
	date5=temperature%10;
		AT24CXX_WriteOneByte(60,tempdate1);
	AT24CXX_WriteOneByte(61,date1);
		AT24CXX_WriteOneByte(62,tempdate2);
	AT24CXX_WriteOneByte(63,date2);
		AT24CXX_WriteOneByte(64,tempdate3);
	AT24CXX_WriteOneByte(65,date3);
		AT24CXX_WriteOneByte(66,tempdate4);
	AT24CXX_WriteOneByte(67,date4);
		AT24CXX_WriteOneByte(68,tempdate5);
	AT24CXX_WriteOneByte(69,date5);
	
		tempdate1=AT24CXX_ReadOneByte(60);    //读取近5次数据
	date1=AT24CXX_ReadOneByte(61);
		tempdate2=AT24CXX_ReadOneByte(62);
	date2=AT24CXX_ReadOneByte(63);
		tempdate3=AT24CXX_ReadOneByte(64);
	date3=AT24CXX_ReadOneByte(65);
		tempdate4=AT24CXX_ReadOneByte(66);
	date4=AT24CXX_ReadOneByte(67);
		tempdate5=AT24CXX_ReadOneByte(68);
	date5=AT24CXX_ReadOneByte(69);
	

}
void tempout_memory(void)   //每一秒读取一次温度数据
{

	readout_temp();

		tempoutdate1=tempoutdate2;
	tempoutdate2=tempoutdate3;
	tempoutdate3=tempoutdate4;
	tempoutdate4=tempoutdate5;
	outdate1=outdate2;
	outdate2=outdate3;
	outdate3=outdate4;
	outdate4=outdate5;
	
	tempoutdate5=temperature/20;
	outdate5=temperature%10;
		AT24CXX_WriteOneByte(70,tempoutdate1);
	AT24CXX_WriteOneByte(71,outdate1);
		AT24CXX_WriteOneByte(72,tempoutdate2);
	AT24CXX_WriteOneByte(73,outdate2);
		AT24CXX_WriteOneByte(74,tempoutdate3);
	AT24CXX_WriteOneByte(75,outdate3);
		AT24CXX_WriteOneByte(76,tempoutdate4);
	AT24CXX_WriteOneByte(77,outdate4);
		AT24CXX_WriteOneByte(78,tempoutdate5);
	AT24CXX_WriteOneByte(79,outdate5);
	
		tempoutdate1=AT24CXX_ReadOneByte(70);    //读取近5次数据
	outdate1=AT24CXX_ReadOneByte(71);
		tempoutdate2=AT24CXX_ReadOneByte(72);
	outdate2=AT24CXX_ReadOneByte(73);
		tempoutdate3=AT24CXX_ReadOneByte(74);
	outdate3=AT24CXX_ReadOneByte(75);
		tempoutdate4=AT24CXX_ReadOneByte(76);
	outdate4=AT24CXX_ReadOneByte(77);
		tempoutdate5=AT24CXX_ReadOneByte(78);
	outdate5=AT24CXX_ReadOneByte(79);
	
	
}

void Temp_display(u8 y,u8 p)            //24<=y<=320-160   温度显示设计函数 page=1
{
	POINT_COLOR=BLUE;
	if(p==0)
	{
		Show_Str(60,3,120,24,"入水口温度",24,0);
	}
		if(p==1)
	{
		Show_Str(60,3,120,24,"出水口温度",24,0);
	}
	LCD_DrawRectangle(5,y,235,y+210);
	LCD_DrawRectangle(4,y-1,236,y+211);
	POINT_COLOR=BLACK;
	Show_Str(30,y+5,180,24,"近5次的温度数据",24,0);
	LCD_DrawLine(6,y+30,234,y+30);
	LCD_DrawLine(6,y+60,234,y+60);
	LCD_DrawLine(6,y+90,234,y+90);
	LCD_DrawLine(6,y+120,234,y+120);
	LCD_DrawLine(6,y+150,234,y+150);
	LCD_DrawLine(6,y+180,234,y+180);
	
	LCD_DrawLine(145,y+30,145,y+180);
	Show_Str(10,y+33,132,24,"第一次温度",24,0);
	Show_Str(10,y+63,132,24,"第二次温度",24,0);
	Show_Str(10,y+93,132,24,"第三次温度",24,0);
	Show_Str(10,y+123,132,24,"第四次温度",24,0);
	Show_Str(10,y+153,132,24,"第五次温度",24,0);
	if(p==0)
	{
		LCD_ShowNum(150,y+37,tempdate1,2,16);
	LCD_ShowString(183,y+37,16,16,16,".");
	LCD_ShowNum(200,y+37,date1,2,16);
		LCD_ShowNum(150,y+67,tempdate2,2,16);
	LCD_ShowString(183,y+67,16,16,16,".");
	LCD_ShowNum(200,y+67,date2,2,16);
		LCD_ShowNum(150,y+97,tempdate3,2,16);
	LCD_ShowString(183,y+97,16,16,16,".");
	LCD_ShowNum(200,y+97,date3,2,16);
		LCD_ShowNum(150,y+127,tempdate4,2,16);
	LCD_ShowString(183,y+127,16,16,16,".");
	LCD_ShowNum(200,y+127,date4,2,16);
		LCD_ShowNum(150,y+157,tempdate5,2,16);
	LCD_ShowString(183,y+157,16,16,16,".");
	LCD_ShowNum(200,y+157,date5,2,16);
	}
	if(p==1)
	{
		LCD_ShowNum(150,y+37,tempoutdate1,2,16);
	LCD_ShowString(183,y+37,16,16,16,".");
	LCD_ShowNum(200,y+37,outdate1,2,16);
		LCD_ShowNum(150,y+67,tempoutdate2,2,16);
	LCD_ShowString(183,y+67,16,16,16,".");
	LCD_ShowNum(200,y+67,outdate2,2,16);
		LCD_ShowNum(150,y+97,tempoutdate3,2,16);
	LCD_ShowString(183,y+97,16,16,16,".");
	LCD_ShowNum(200,y+97,outdate3,2,16);
		LCD_ShowNum(150,y+127,tempoutdate4,2,16);
	LCD_ShowString(183,y+127,16,16,16,".");
	LCD_ShowNum(200,y+127,outdate4,2,16);
		LCD_ShowNum(150,y+157,tempoutdate5,2,16);
	LCD_ShowString(183,y+157,16,16,16,".");
	LCD_ShowNum(200,y+157,outdate5,2,16);
	}
	POINT_COLOR=RED;
	Show_Str(10,y+183,96,24,"数据清零",24,0);
	Show_Str(185,y+183,48,24,"返回",24,0);
	POINT_COLOR=BLACK;
}









