#include "memory.h" 
#include "delay.h"
#include "at24c02.h" 
#include "ds18b20.h"
#include "math.h"
#include "lcd.h"
#include "text.h"

short temperature; 
void read_temp(void)
{
	temperature=DS18B20_Get_Temp();	
	if(temperature<0)
	{
		LCD_ShowChar(60+40,150,'-',16,0);			//显示负号
		temperature=-temperature;					//转为正数
	}
}

void temp_memory(void)
{
	u8 date1,date2;
	read_temp();
	AT24CXX_WriteOneByte(60,temperature/10);
	AT24CXX_WriteOneByte(61,temperature%10);
	date1=AT24CXX_ReadOneByte(60);
	date2=AT24CXX_ReadOneByte(61);
	LCD_ShowNum(115,9,date1,2,16);
	LCD_ShowNum(150,9,date2,1,16);
	LCD_ShowNum(115,61,temperature/10,2,16);
	LCD_ShowNum(150,61,temperature%10,2,16);
}










