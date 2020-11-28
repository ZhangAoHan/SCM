/***************************************************
*驱动名称：LGM12641BS1R液晶屏驱动
*驱动说明：将lcd的操作函数化，简单实现操作
*作者：yd
*时间：09.06.20
***************************************************/
#ifndef LCD_12864
#define LCD_12864
#include "kongzhi.h"
#ifndef LCD_GLOBAL
  #define LCD_EXT extern 
#else
  #define LCD_EXT
#endif
/***************************12864管脚配置*********************************/
#define   port   P0
sbit  rs=P2^6;
sbit  rw=P2^7;
sbit   e=P3^0;
sbit cs2=P2^5;
sbit cs1=P2^4;
LCD_EXT void Lcd_Display_On(void);              //LCD显示开
LCD_EXT void Lcd_Display_Off(void);             //LCD显示关
LCD_EXT void Lcd_Set_X(uchar x);                //LCD设置X坐标
LCD_EXT void Lcd_Set_Y(uchar y);                //LCD设置Y坐标
LCD_EXT void Lcd_Set_X_Y(uchar x, uchar y);     //LCD设置x y坐标
LCD_EXT void Lcd_Write_Command(uchar temp);     //写指令代码
LCD_EXT void Lcd_Write_Byte(uchar temp);	    //写数据
//显示16X8字符(字母),bit_flag = 1 正常显示  bit_flag = 0 黑白反相显示 
LCD_EXT void Lcd_Character_16X8( bit bit_flag, uchar x, uchar y, uchar code *point );
//显示16*16字符（汉字）,bit_flag = 1 正常显示 bit_flag = 0 黑白反相显示
LCD_EXT void Lcd_Character_16X16( bit bit_flag, uchar x, uchar y, uchar code *point);
LCD_EXT void Lcd_Clear(void);                   //清屏
LCD_EXT void Lcd_Initial(void);                 //初始化LCD              
#endif