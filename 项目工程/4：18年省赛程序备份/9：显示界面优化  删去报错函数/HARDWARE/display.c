//显示子函数
/*
	1：页面设计（2个页面（猜拳识别页面和数字识别页面））
*/


#include "display.h"	 

void C_display_init(void)   //猜拳界面初始化设计
{
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(1,1 ,239 ,27);   //画矩形  显示状态   显示范围（2-238  2-26）
	
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(1,29 ,239 ,55);   //画矩形  显示结果  显示范围（180-228（二位汉字，不足补空格） 30-54）
	POINT_COLOR=BLACK;
	Show_Str(2,30,168,24,"判决结果显示：",24,1);
	
	POINT_COLOR=RED;
	LCD_DrawRectangle(1,57 ,150 ,83);   //画矩形 触摸按键
	POINT_COLOR=BLACK;
	Show_Str(2,58,144,24,"进入识数界面",24,0);
	
	POINT_COLOR=YELLOW;
	LCD_DrawRectangle(1,85 ,239 ,245);   //画矩形  显示判决数据
	LCD_DrawRectangle(1,135 ,130 ,245);   //画矩形 
	LCD_DrawRectangle(130,135 ,239 ,245);   //画矩形 
	LCD_DrawRectangle(1,136,55 ,245);   //画矩形 
	LCD_Fill(2,137,54,159,MAGENTA);
	LCD_DrawLine(1,160,239,160);
	LCD_DrawLine(1,187,239,187);
	LCD_DrawLine(1,217,239,217);
	POINT_COLOR=BLACK;
	Show_Str(2,86,192,24,"判决数据显示区域",24,0);
	Show_Str(2,110,144,24,"通道2数据：",24,0);   //显示范围（150-240   110-134）
	Show_Str(65,136,48,24,"中值",24,0);
	Show_Str(154,136,48,24,"阈值",24,0);
	Show_Str(2,160,48,24,"石头",24,0);
	Show_Str(2,190,48,24,"剪刀",24,0);
	Show_Str(2,220,48,24,"布",24,0);
}

void S_display_init(void)    //数字识别初始化设计
{
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(1,1 ,239 ,27);   //画矩形  显示状态   显示范围（2-238  2-26）
	
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(1,29 ,239 ,55);   //画矩形  显示结果  显示范围（180-228（二位汉字，不足补空格） 30-54）
	POINT_COLOR=BLACK;
	Show_Str(2,30,168,24,"判决结果显示：",24,1);
	
	POINT_COLOR=RED;
	LCD_DrawRectangle(1,57 ,150 ,83);   //画矩形 触摸按键
	POINT_COLOR=BLACK;
	Show_Str(2,58,144,24,"进入猜拳界面",24,0);
	POINT_COLOR=YELLOW;
	LCD_DrawRectangle(1,85 ,239 ,307);   //画矩形  显示判决数据
	LCD_DrawRectangle(1,135 ,130 ,307);   //画矩形 
	LCD_DrawRectangle(130,135 ,239 ,307);   //画矩形 
	LCD_DrawRectangle(1,136,55 ,307);   //画矩形 
	LCD_Fill(2,137,54,159,MAGENTA);
	LCD_DrawLine(1,161,239,161);
	LCD_DrawLine(1,188,239,188);
	LCD_DrawLine(1,217,239,217);
	LCD_DrawLine(1,247,239,247);
	LCD_DrawLine(1,277,239,277);
	POINT_COLOR=BLACK;
	Show_Str(2,86,192,24,"判决数据显示区域",24,0);
	Show_Str(2,110,144,24,"通道2数据：",24,0);   //显示范围（150-240   110-134）
	Show_Str(65,136,48,24,"中值",24,0);
	Show_Str(154,136,48,24,"阈值",24,0);
	Show_Str(2,162,48,24,"测1",24,0);
	Show_Str(2,190,48,24,"测2",24,0);
	Show_Str(2,220,48,24,"测3",24,0);
	Show_Str(2,250,48,24,"测4",24,0);
	Show_Str(2,280,48,24,"测5",24,0);
}
