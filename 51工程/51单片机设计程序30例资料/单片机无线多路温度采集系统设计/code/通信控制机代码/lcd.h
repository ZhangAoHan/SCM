/***********************************************************************
*文件名称：lcd.h
*说明：本文件为液晶显示器驱动函数头文件
*功能：1.端口定义
       2.驱动函数声明
*修改：无
*版本：V1.0.0
*作者：YuanDong
*时间：2009.07.03
*************************************************************************/
#ifndef LCD_12864
#define LCD_12864
#include "Include.h"
#ifndef LCD_GLOBAL
  #define LCD_EXT extern 
#else
  #define LCD_EXT
#endif
/***************************12864管脚配置*********************************/
#define   port   P0
sbit  rs=P1^0;
sbit  rw=P1^1;
sbit   e=P1^2;
sbit cs1=P3^6;
sbit cs2=P3^7;
LCD_EXT void Delay(uint a);                 //延迟时间=a*1ms
LCD_EXT void Lcd_Display_On();              //LCD显示开
LCD_EXT void Lcd_Display_Off();             //LCD显示关
LCD_EXT void Lcd_Set_X(uchar x);            //LCD设置X坐标
LCD_EXT void Lcd_Set_Y(uchar y);            //LCD设置Y坐标
LCD_EXT void Lcd_Set_X_Y(uchar x, uchar y); //LCD设置x y坐标
LCD_EXT void Lcd_Write_Command(uchar temp); //写指令代码
LCD_EXT void Lcd_Write_Byte(uchar temp);	//写数据
//显示16X8字符(字母),bit_flag = 1 正常显示  bit_flag = 0 黑白反相显示 
LCD_EXT void Lcd_Character_16X8( bit bit_flag, uchar x, uchar y, uchar code *point );
//显示16*16字符（汉字）,bit_flag = 1 正常显示 bit_flag = 0 黑白反相显示
LCD_EXT void Lcd_Character_16X16( bit bit_flag, uchar x, uchar y, uchar code *point);
LCD_EXT void Lcd_Clear();                   //清屏
LCD_EXT void Lcd_Initial();                 //初始化LCD              
#endif
