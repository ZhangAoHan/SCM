/***************************************************
*驱动名称：LGM12641BS1R液晶屏驱动
*驱动说明：将lcd的操作函数化，简单实现操作
*作者：yd
*时间：09.06.20
***************************************************/
#ifndef LCD_12864
#define LCD_12864
#include "Include.h"
#ifndef LCD_GLOBAL
  #define LCD_EXT extern 
#else
  #define LCD_EXT
#endif
/***************************12864管脚配置*********************************/
#define   port   P1
sbit  rs=P3^0;
sbit  rw=P3^1;
sbit   e=P3^2;
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
LCD_EXT void Lcd_Time(uchar * clock_time);	//显示"hour时min分sec秒"  
LCD_EXT void Lcd_Data(uchar * clock_time);  //显示日期
LCD_EXT void Lcd_Week(uchar week);          //显示星期 
LCD_EXT void Lcd_Clock(uchar * clock_time); //显示时钟
LCD_EXT void Lcd_Lunar_Calendar(uchar * lunar_canlendar); //显示农历
LCD_EXT void Lcd_Temperture(uchar * temperature);         //显示温度
LCD_EXT void Lcd_Set_Clock( uchar temp, uchar *point );   //显示调整的时间
LCD_EXT void Lcd_Function( uchar temp );                  //滚动显示 时间设置 闹钟设置
LCD_EXT void Lcd_Alarm( uchar temp, uchar * alarm_time ); //闹钟调整画面显示
LCD_EXT void LCD_ERSHI( uchar temp );                     //显示节气                
#endif