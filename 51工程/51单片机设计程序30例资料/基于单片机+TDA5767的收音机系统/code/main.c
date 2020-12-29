/*******************************************************
* 文件名称：main.c                          
* 说明：本文件为收音机的主函数
* 功能：1.命令发送，接收 
        2.调用函数
* 修改： 无
* 版本：1.0.0
* 作者：YuanDong 
* 时间：2009.7.20
*********************************************************/
#include <AT89X52.h>
#include "iic.h"
#include "3310LCD_function.c"
#define uchar unsigned char
#define uint  unsigned int
#define SLA_W 0b11000000
#define SLA_R 0b11000001

uchar senddata[5] ;
uchar readdata[5] ;
uchar search = 0;
uchar search_up = 0;
//--------------延时-----------------  
/********************************************************
*函数名称：void delay_ms(uint ms)
*函数功能：延时ms
*函数入口：ms
*函数出口：无
********************************************************/
void delay_ms(uint ms)
{
	uint i,j;
	for(i=0;i<ms;i++)
	{
	  j=1000;
	  while(j--); 
	}
}
 
/********************************************************
*函数名称：void set5767(void)
*函数功能：设定收音机频率
*函数入口：无
*函数出口：无
********************************************************/
void set5767(void)
{
	uchar i = 0;
	iic_write(SLA_W);	//发送地址
	delay_ms(10);
	for ( i = 0; i < 5; i++ )
	{
	  iic_write(senddata[i]); //发送数据
	  delay_ms(10);
	}
}  
/********************************************************
*函数名称：void read5767(void)
*函数功能：读取收音机频率
*函数入口：无
*函数出口：无
********************************************************/
void read5767(void)
{
	uchar i = 0;
	iic_write(SLA_R);	  //发送地址
	for ( i = 0; i < 5; i++ )
	{
	  readdata[i] =iic_read();
	  delay_ms(10);	
	}
}

/********************************************************
*函数名称：void show_frequency(void)		
*函数功能：智能显示收音机频率
*函数入口：无
*函数出口：无
********************************************************/
void show_frequency(void)		
{
	uint32_t nPLL =0;			    //Dec 
	uint32_t frequency = 0;	        //Khz
	uchar display_bit[5];
	
	uchar tbTmp1=readdata[1];
	uchar tbTmp2=readdata[0];
	tbTmp2&=0x3f;

	nPLL=tbTmp2*256+tbTmp1;
          
	// calculate searched station frequency  
    if(senddata[2]&0x10)
		frequency =(unsigned long)(nPLL*82/10-225);
    else
		frequency =(unsigned long)(nPLL*82/10+225);
		
	display_bit[0] = frequency / 100000 ;
	if ( display_bit[0] == 0 ) display_bit[0] = 0x20;
	else display_bit[0] += 0x30;
	
	display_bit[1] = (frequency / 10000)%10 +0x30;
	display_bit[2] = (frequency / 1000)%10 +0x30;
	display_bit[3] = (frequency / 100)%10 +0x30;
	display_bit[4] = (frequency / 10)%10 +0x30;
	LCD_write_english_string(0,2," " );
	 LCD_write_char(display_bit[0]);
	 LCD_write_char(display_bit[1]);
	 LCD_write_char(display_bit[2]);
	 LCD_write_english_string(25,2,"." );
	 LCD_write_char(display_bit[3]);
	 LCD_write_char(display_bit[4]);
	 LCD_write_english_string(43,2," MHz" );
   
}	
/********************************************************
*函数名称：void show_rx_power(void)		
*函数功能：智能显示收音机频率
*函数入口：无
*函数出口：无
********************************************************/
void show_rx_power(void)
{
	uchar temp;
	
	temp = (readdata[3]>>4);
	
	LCD_write_english_string(60,0," ");
	
	LCD_write_char((temp/10)%10 + 0x30 );
	LCD_write_char(temp%10 + 0x30 );
}
   
/********************************************************
*函数名称：void main(void)		
*函数功能：调用各个函数
*函数入口：无
*函数出口：无
********************************************************/
void main(void)
{
	senddata[0] = 0b01101111;  //load 100MHz pll
	senddata[1] = 0b10010011;  // away's low side injection
	senddata[2] = 0b00100000;
	senddata[3] = 0b10010000;                                                                  
	senddata[4] = 0b00000000;
	readdata[0] = senddata[0];
	readdata[1] = senddata[1];
	
	LCD_write_english_string(0,0,"FM STEREO" );	
	LCD_write_english_string(0,2,"  99.1Mhz" );
	show_frequency();
	LCD_write_inverse_string(0,5,"  UP  ");
	LCD_write_inverse_string(48,5," DOWN ");
	
	while(1)
	{
	
		if ( P3_1==0 )     //清零按键
		{
			delay_nms(20);
			if ( bit_is_clear( PIND,3))
			{
				loop_until_bit_is_set(PIND, 3);
				LCD_write_english_string(0,4,"KEY1 press" );
				senddata[2] &= 0x7f;   // set search down
				set5767();
				LCD_write_english_string(0,4,"searching down" );
				search_up = 0;
				search = 1;
			}
		}
		
		if ( P3_2==0 )
		{
			delay_nms(20);
			if ( bit_is_clear( PIND,2))
			{
				
				loop_until_bit_is_set(PIND, 2);
				LCD_write_english_string(0,4,"KEY2 press" );
				senddata[2] |= 0x80;   // set search up
				set5767();
				LCD_write_english_string(0,4,"searching up  ");
				search_up = 1;
				search = 1;
				
			}
		}
		if ( search )
		{
			read5767();
			if ( readdata[0] & 0x40 )  //reach band end
			{
				if ( search_up )
				{
					senddata[0] = 0b01101001;    // load 88Mhz pll
					senddata[1] = 0b11011010;
					set5767();
				}
				else                  
				{
					senddata[0] = 0b01110011;    // load 108Mhz pll
					senddata[1] = 0b01100100;
					set5767();
				}
			}
			if ( readdata[0] & 0x80)   //has been found a station
			{
				show_frequency();
				show_rx_power();
				senddata[0] = ((readdata[0] & 0x3f) |0x40);
				senddata[1] = readdata[1];  //record the pll	
				search = 0;
			}
			
		}
		
	}
}
