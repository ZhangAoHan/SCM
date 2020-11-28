/***************************************************
*�������ƣ�LGM12641BS1RҺ��������
*����˵������lcd�Ĳ�������������ʵ�ֲ���
*���ߣ�yd
*ʱ�䣺09.06.20
***************************************************/
#ifndef LCD_12864
#define LCD_12864
#include "Include.h"
#ifndef LCD_GLOBAL
  #define LCD_EXT extern 
#else
  #define LCD_EXT
#endif
/***************************12864�ܽ�����*********************************/
#define   port   P1
sbit  rs=P3^0;
sbit  rw=P3^1;
sbit   e=P3^2;
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
LCD_EXT void Lcd_Time(uchar * clock_time);	//��ʾ"hourʱmin��sec��"  
LCD_EXT void Lcd_Data(uchar * clock_time);  //��ʾ����
LCD_EXT void Lcd_Week(uchar week);          //��ʾ���� 
LCD_EXT void Lcd_Clock(uchar * clock_time); //��ʾʱ��
LCD_EXT void Lcd_Lunar_Calendar(uchar * lunar_canlendar); //��ʾũ��
LCD_EXT void Lcd_Temperture(uchar * temperature);         //��ʾ�¶�
LCD_EXT void Lcd_Set_Clock( uchar temp, uchar *point );   //��ʾ������ʱ��
LCD_EXT void Lcd_Function( uchar temp );                  //������ʾ ʱ������ ��������
LCD_EXT void Lcd_Alarm( uchar temp, uchar * alarm_time ); //���ӵ���������ʾ
LCD_EXT void LCD_ERSHI( uchar temp );                     //��ʾ����                
#endif