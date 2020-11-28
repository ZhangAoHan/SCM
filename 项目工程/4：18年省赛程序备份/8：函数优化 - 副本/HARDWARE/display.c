//显示子函数
/*
	1：页面设计（2个页面（猜拳识别页面和数字识别页面））
*/


#include "display.h"	 

void C_display_init(void)   //猜拳界面初始化设计
{
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(10,60 ,230 ,310);   //画矩形  蓝色
	POINT_COLOR=BLACK;
	Show_Str(11,61,192,24,"进入数字识别界面",24,0);   //触摸进入数字识别界面
	Show_Str(11,90,84,24,"通道2：",24,0);
	POINT_COLOR=BLUE;	
	Show_Str(60,150,48,24,"阈值",24,0);
	Show_Str(120,150,96,24,"波动范围",24,0);	
	POINT_COLOR=BLACK;
	Show_Str(11,180,48,24,"石头",24,0);
	Show_Str(11,210,48,24,"剪刀",24,0);
	Show_Str(11,240,48,24,"布",24,0);
}

void S_display_init(void)    //数字识别初始化设计
{
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(10,60 ,230 ,310);   //画矩形
	POINT_COLOR=BLACK;
	Show_Str(11,61,192,24,"进入猜拳识别界面",24,0);
	POINT_COLOR=RED;   
	Show_Str(11,90,84,24,"通道2：",24,0);
	POINT_COLOR=BLUE;	
	Show_Str(60,120,48,24,"阈值",24,0);
	Show_Str(120,120,96,24,"波动范围",24,0);
	POINT_COLOR=BLACK;
	Show_Str(11,150,48,24,"测1",24,0);
	Show_Str(11,180,48,24,"测2",24,0);
	Show_Str(11,210,48,24,"测3",24,0);
	Show_Str(11,240,48,24,"测4",24,0);
	Show_Str(11,270,48,24,"测5",24,0);
}
