/********************************************************************
*�������ƣ�
********************************************************************/
#ifndef LCD_12864
#define LCD_12864
#include "Include.h"
#ifndef LCD_GLOBAL
  #define LCD_EXT extern 
#else
  #define LCD_EXT
#endif
/***************************12864�ܽ�����*********************************/
#define   port   P0
sbit  rs=P2^2;
sbit  rw=P2^1;
sbit   e=P2^0;
sbit cs1=P2^3;
sbit cs2=P2^4;
LCD_EXT void Lcd_Display_On(void);              //LCD��ʾ��
LCD_EXT void Lcd_Display_Off(void);             //LCD��ʾ��
LCD_EXT void Lcd_Set_X(uchar x);            //LCD����X����
LCD_EXT void Lcd_Set_Y(uchar y);            //LCD����Y����
LCD_EXT void Lcd_Set_X_Y(uchar x, uchar y); //LCD����x y����
LCD_EXT void Lcd_Write_Command(uchar temp); //дָ�����
LCD_EXT void Lcd_Write_Byte(uchar temp);	//д����
//��ʾ16X8�ַ�(��ĸ),bit_flag = 1 ������ʾ  bit_flag = 0 �ڰ׷�����ʾ 
LCD_EXT void Lcd_Character_16X8( bit bit_flag, uchar x, uchar y, uchar code *point );
//��ʾ16*16�ַ������֣�,bit_flag = 1 ������ʾ bit_flag = 0 �ڰ׷�����ʾ
LCD_EXT void Lcd_Character_16X16( bit bit_flag, uchar x, uchar y, uchar code *point);
LCD_EXT void Lcd_Clear(void);                   //����
LCD_EXT void Lcd_Initial(void);                 //��ʼ��LCD              
#endif