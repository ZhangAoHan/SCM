/*******************************************************
* 文件名称：3310lcd_function.c                          
* 说明：lcd驱动函数
* 功能：驱动LCD
* 修改： 无
* 版本：1.0.0
* 作者：YuanDong 
* 时间：2009.7.20
*********************************************************/
#include <AT89X52.h>
#include "english_6x8_pixel.h"
#include "delay_function.C"
#include "spi.h"
//---------------lcd端口定义------------------
#define LCD_DC                 P2_1
#define LCD_CE                 P2_2
#define SPI_MOSI               P2_3
#define LCD_RST                P2_4
#define SPI_CLK                P2_5
//--------------------------------------------
void LCD_init(void);

void LCD_clear(void);

void LCD_write_english_string(unsigned char X,unsigned char Y,char *s);

void LCD_write_chinese_string(unsigned char X, unsigned char Y,
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row);                 

void LCD_write_char(unsigned char c);

void LCD_write_byte(unsigned char dat, unsigned char command);

void delay_1us(void);                 
void delay_nus(unsigned int n);      
void delay_1ms(void);                
void delay_nms(unsigned int n);      
/********************************************************
*函数名称：void LCD_init(void)
*函数功能：3310LCD初始化
*函数入口：无
*函数出口：无	  
********************************************************/
void LCD_init(void)
{        
	LCD_RST =0;			   // 产生一个让LCD复位的低电平脉冲
    delay_1us();
	LCD_RST =1;		
	LCD_CE =0;					// 关闭LCD
    delay_1us();
	LCD_CE =1;				    // 使能LCD	
    delay_1us();
    LCD_write_byte(0x21, 0);	// 使用扩展命令设置LCD模式
    LCD_write_byte(0xc8, 0);	// 设置偏置电压
    LCD_write_byte(0x06, 0);	// 温度校正
    LCD_write_byte(0x13, 0);	// 1:48
    LCD_write_byte(0x20, 0);	// 使用基本命令
    LCD_clear();	        // 清屏
    LCD_write_byte(0x0c, 0);	// 设定显示模式，正常显示
	LCD_CE =0;   				// 关闭LCD        
}

/********************************************************
*函数名称：void LCD_clear(void)
*函数功能：LCD清屏函数
*函数入口：无
*函数出口：无	  
********************************************************/
void LCD_clear(void)
{
    unsigned int i;

    LCD_write_byte(0x0c, 0);			
    LCD_write_byte(0x80, 0);			

    for (i=0; i<504; i++)
      LCD_write_byte(0, 1);			
}
 
/********************************************************
*函数名称：void LCD_set_XY(unsigned char X, unsigned char Y)
*函数功能：设置LCD坐标函数
*函数入口：x，y
*函数出口：无	  
********************************************************/
void LCD_set_XY(unsigned char X, unsigned char Y)
{
    LCD_write_byte(0x40 | Y, 0);		// column
    LCD_write_byte(0x80 | X, 0);          	// row
}

/********************************************************
*函数名称：void LCD_write_char(unsigned char c)
*函数功能：显示英文字符
*函数入口：c
*函数出口：无	  
********************************************************/
void LCD_write_char(unsigned char c)
{
    unsigned int line;
    c -= 32;
    for (line=0; line<6; line++)
      LCD_write_byte(font6x8[c][line], 1);
}

/********************************************************
*函数名称：void LCD_write_inverse_char(unsigned char c)
*函数功能：字符转换
*函数入口：c
*函数出口：无	  
********************************************************/
void LCD_write_inverse_char(unsigned char c)
{
    unsigned int line;
    c -= 32;
    for (line=0; line<6; line++)
      LCD_write_byte(~font6x8[c][line], 1);
}
	
/********************************************************
*函数名称：void LCD_write_english_string(unsigned char X,unsigned char Y,char *s)
*函数功能：英文字符串显示函数
*函数入口：X,Y,*s
*函数出口：无	  
********************************************************/
void LCD_write_english_string(unsigned char X,unsigned char Y,char *s)
  {
    LCD_set_XY(X,Y);
    while (*s) 
    {
		LCD_write_char(*s);
		s++;
    }
  }
 	
/********************************************************
*函数名称：void LCD_write_inverse_string(unsigned char X,unsigned char Y,char *s)
*函数功能：英文字符串字码转换
*函数入口：X,Y,*s
*函数出口：无	  
********************************************************/
void LCD_write_inverse_string(unsigned char X,unsigned char Y,char *s)
{
    LCD_set_XY(X,Y);
    while (*s) 
    {
		LCD_write_inverse_char(*s);
		s++;
    }
}

/********************************************************
*函数名称：void LCD_write_byte(unsigned char dat, unsigned char command)
*函数功能：使用SPI接口写数据到LCD
*函数入口：dat，command
*函数出口：无	  
********************************************************/
void LCD_write_byte(unsigned char dat, unsigned char command)
{		        
    LCD_CE =0;  	        // 使能LCD
    if (command == 0)
	   LCD_DC =0;		    // 传送命令        
    else		        
	  LCD_DC =1;		   // 传送数据
	SPISendByte(dat);	   //通过SPI口发送数据		
	LCD_CE =1;			   // 关闭LCD
}
 
/********************************************************
*函数名称：void lcd_inverse(void)
*函数功能：输入控制命令
*函数入口：无
*函数出口：无	  
********************************************************/
void lcd_inverse(void)
{
	LCD_write_byte(0b00001101,0);
}

void lcd_no_inverse(void)
{
	LCD_write_byte(0b00001100,0);
}
