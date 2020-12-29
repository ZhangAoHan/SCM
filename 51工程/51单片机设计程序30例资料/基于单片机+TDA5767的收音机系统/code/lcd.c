/*******************************************************
* �ļ����ƣ�3310lcd_function.c                          
* ˵����lcd��������
* ���ܣ�����LCD
* �޸ģ� ��
* �汾��1.0.0
* ���ߣ�YuanDong 
* ʱ�䣺2009.7.20
*********************************************************/
#include <AT89X52.h>
#include "english_6x8_pixel.h"
#include "delay_function.C"
#include "spi.h"
//---------------lcd�˿ڶ���------------------
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
*�������ƣ�void LCD_init(void)
*�������ܣ�3310LCD��ʼ��
*������ڣ���
*�������ڣ���	  
********************************************************/
void LCD_init(void)
{        
	LCD_RST =0;			   // ����һ����LCD��λ�ĵ͵�ƽ����
    delay_1us();
	LCD_RST =1;		
	LCD_CE =0;					// �ر�LCD
    delay_1us();
	LCD_CE =1;				    // ʹ��LCD	
    delay_1us();
    LCD_write_byte(0x21, 0);	// ʹ����չ��������LCDģʽ
    LCD_write_byte(0xc8, 0);	// ����ƫ�õ�ѹ
    LCD_write_byte(0x06, 0);	// �¶�У��
    LCD_write_byte(0x13, 0);	// 1:48
    LCD_write_byte(0x20, 0);	// ʹ�û�������
    LCD_clear();	        // ����
    LCD_write_byte(0x0c, 0);	// �趨��ʾģʽ��������ʾ
	LCD_CE =0;   				// �ر�LCD        
}

/********************************************************
*�������ƣ�void LCD_clear(void)
*�������ܣ�LCD��������
*������ڣ���
*�������ڣ���	  
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
*�������ƣ�void LCD_set_XY(unsigned char X, unsigned char Y)
*�������ܣ�����LCD���꺯��
*������ڣ�x��y
*�������ڣ���	  
********************************************************/
void LCD_set_XY(unsigned char X, unsigned char Y)
{
    LCD_write_byte(0x40 | Y, 0);		// column
    LCD_write_byte(0x80 | X, 0);          	// row
}

/********************************************************
*�������ƣ�void LCD_write_char(unsigned char c)
*�������ܣ���ʾӢ���ַ�
*������ڣ�c
*�������ڣ���	  
********************************************************/
void LCD_write_char(unsigned char c)
{
    unsigned int line;
    c -= 32;
    for (line=0; line<6; line++)
      LCD_write_byte(font6x8[c][line], 1);
}

/********************************************************
*�������ƣ�void LCD_write_inverse_char(unsigned char c)
*�������ܣ��ַ�ת��
*������ڣ�c
*�������ڣ���	  
********************************************************/
void LCD_write_inverse_char(unsigned char c)
{
    unsigned int line;
    c -= 32;
    for (line=0; line<6; line++)
      LCD_write_byte(~font6x8[c][line], 1);
}
	
/********************************************************
*�������ƣ�void LCD_write_english_string(unsigned char X,unsigned char Y,char *s)
*�������ܣ�Ӣ���ַ�����ʾ����
*������ڣ�X,Y,*s
*�������ڣ���	  
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
*�������ƣ�void LCD_write_inverse_string(unsigned char X,unsigned char Y,char *s)
*�������ܣ�Ӣ���ַ�������ת��
*������ڣ�X,Y,*s
*�������ڣ���	  
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
*�������ƣ�void LCD_write_byte(unsigned char dat, unsigned char command)
*�������ܣ�ʹ��SPI�ӿ�д���ݵ�LCD
*������ڣ�dat��command
*�������ڣ���	  
********************************************************/
void LCD_write_byte(unsigned char dat, unsigned char command)
{		        
    LCD_CE =0;  	        // ʹ��LCD
    if (command == 0)
	   LCD_DC =0;		    // ��������        
    else		        
	  LCD_DC =1;		   // ��������
	SPISendByte(dat);	   //ͨ��SPI�ڷ�������		
	LCD_CE =1;			   // �ر�LCD
}
 
/********************************************************
*�������ƣ�void lcd_inverse(void)
*�������ܣ������������
*������ڣ���
*�������ڣ���	  
********************************************************/
void lcd_inverse(void)
{
	LCD_write_byte(0b00001101,0);
}

void lcd_no_inverse(void)
{
	LCD_write_byte(0b00001100,0);
}
