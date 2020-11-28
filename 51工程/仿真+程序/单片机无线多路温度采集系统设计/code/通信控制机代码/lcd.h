/***********************************************************************
*�ļ����ƣ�lcd.h
*˵�������ļ�ΪҺ����ʾ����������ͷ�ļ�
*���ܣ�1.�˿ڶ���
       2.������������
*�޸ģ���
*�汾��V1.0.0
*���ߣ�YuanDong
*ʱ�䣺2009.07.03
*************************************************************************/
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
sbit  rs=P1^0;
sbit  rw=P1^1;
sbit   e=P1^2;
sbit cs1=P3^6;
sbit cs2=P3^7;
LCD_EXT void Delay(uint a);                 //�ӳ�ʱ��=a*1ms
LCD_EXT void Lcd_Display_On();              //LCD��ʾ��
LCD_EXT void Lcd_Display_Off();             //LCD��ʾ��
LCD_EXT void Lcd_Set_X(uchar x);            //LCD����X����
LCD_EXT void Lcd_Set_Y(uchar y);            //LCD����Y����
LCD_EXT void Lcd_Set_X_Y(uchar x, uchar y); //LCD����x y����
LCD_EXT void Lcd_Write_Command(uchar temp); //дָ�����
LCD_EXT void Lcd_Write_Byte(uchar temp);	//д����
//��ʾ16X8�ַ�(��ĸ),bit_flag = 1 ������ʾ  bit_flag = 0 �ڰ׷�����ʾ 
LCD_EXT void Lcd_Character_16X8( bit bit_flag, uchar x, uchar y, uchar code *point );
//��ʾ16*16�ַ������֣�,bit_flag = 1 ������ʾ bit_flag = 0 �ڰ׷�����ʾ
LCD_EXT void Lcd_Character_16X16( bit bit_flag, uchar x, uchar y, uchar code *point);
LCD_EXT void Lcd_Clear();                   //����
LCD_EXT void Lcd_Initial();                 //��ʼ��LCD              
#endif
