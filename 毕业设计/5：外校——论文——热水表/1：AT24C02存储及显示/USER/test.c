#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "lcd.h"
#include "touch.h"  
#include "w25q128.h"  
#include "text.h"
#include "ds18b20.h"   
#include "memory.h" 
//void rtp_test(void);
//void Load_Drow_Dialog(void);
//void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color);
//u16 my_abs(u16 x1,u16 x2);
//void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color);
//void test_touch(void)
//{
//	tp_dev.scan(0); 
//if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
//{
//	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
//	{
//		if(tp_dev.x[0]>11&&tp_dev.x[0]<150&&tp_dev.y[0]>10&&tp_dev.y[0]<80)
//		{
//			Show_Str(50,200,24,24,"对",24,0);
//		}
//		else if(tp_dev.x[0]>11&&tp_dev.x[0]<150&&tp_dev.y[0]>100&&tp_dev.y[0]<170)
//		{
//			Show_Str(50,200,24,24,"错",24,0);
//		}
//		else if(tp_dev.x[0]>150&&tp_dev.x[0]<200&&tp_dev.y[0]>200&&tp_dev.y[0]<230)
//		{
//			TP_Adjust();
//		}
//		else
//		{
//			Show_Str(50,200,24,24,"无",24,0);
//			LCD_ShowxNum(10,240,tp_dev.x[0],9,16,0);
//			LCD_ShowxNum(10,280,tp_dev.y[0],9,16,0);

//		}
//	}
//}	
//	else Show_Str(50,200,24,24,"浪",24,0);
//}
//清空屏幕并在右上角显示"RST"
//void Load_Drow_Dialog(void)
//{
//	LCD_Clear(WHITE);	//清屏   
// 	POINT_COLOR=BLUE;	//设置字体为蓝色 
//	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
//  	POINT_COLOR=RED;	//设置画笔蓝色 
//}

// //5个触控点的颜色												 
//const u16 POINT_COLOR_TBL[CT_MAX_TOUCH]={RED,GREEN,BLUE,BROWN,GRED};  
////电阻触摸屏测试函数
//void rtp_test(void)
//{  
//	while(1)
//	{
//		tp_dev.scan(0); 		 
//		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
//		{	
//		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
//			{	
//				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//清除
//				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//画图	  			   
//			}
//		}else delay_ms(10);	//没有按键按下的时候 	    
//	}
//}

int main(void)
{				 
 
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	LCD_Init();
	W25QXX_Init();				//初始化W25Q128 和SPI2
	tp_dev.init();			//触摸屏初始化 
	while(font_init()) 			//检查字库
	{;}  
	while(DS18B20_Init())	//DS18B20初始化	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	Show_Str(5,5,132,24,"第一次数据：",24,0);
	Show_Str(5,35,132,24,"第二次数据：",24,0);
	Show_Str(5,65,108,24,"温度数据：",24,0);
//		LCD_DrawRectangle(10,10,150,80);
//		LCD_ShowString(11,11,80,16,16,"right");
//		LCD_DrawRectangle(10,100,150,170);
//		LCD_ShowString(11,101,64,16,16,"left");
//		Show_Str(150,200,48,24,"校准",24,0);
  	while(1)
	{
////		test_touch();
//		rtp_test(); 	
//LCD_ShowChar(60+40,150,' ',16,0);			//去掉负号
//			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//显示正数部分	    
//   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//显示小数部分 	
		temp_memory();
	}	 
} 






