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
//if(tp_dev.sta&TP_PRES_DOWN)			//������������
//{
//	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
//	{
//		if(tp_dev.x[0]>11&&tp_dev.x[0]<150&&tp_dev.y[0]>10&&tp_dev.y[0]<80)
//		{
//			Show_Str(50,200,24,24,"��",24,0);
//		}
//		else if(tp_dev.x[0]>11&&tp_dev.x[0]<150&&tp_dev.y[0]>100&&tp_dev.y[0]<170)
//		{
//			Show_Str(50,200,24,24,"��",24,0);
//		}
//		else if(tp_dev.x[0]>150&&tp_dev.x[0]<200&&tp_dev.y[0]>200&&tp_dev.y[0]<230)
//		{
//			TP_Adjust();
//		}
//		else
//		{
//			Show_Str(50,200,24,24,"��",24,0);
//			LCD_ShowxNum(10,240,tp_dev.x[0],9,16,0);
//			LCD_ShowxNum(10,280,tp_dev.y[0],9,16,0);

//		}
//	}
//}	
//	else Show_Str(50,200,24,24,"��",24,0);
//}
//�����Ļ�������Ͻ���ʾ"RST"
//void Load_Drow_Dialog(void)
//{
//	LCD_Clear(WHITE);	//����   
// 	POINT_COLOR=BLUE;	//��������Ϊ��ɫ 
//	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
//  	POINT_COLOR=RED;	//���û�����ɫ 
//}

// //5�����ص����ɫ												 
//const u16 POINT_COLOR_TBL[CT_MAX_TOUCH]={RED,GREEN,BLUE,BROWN,GRED};  
////���败�������Ժ���
//void rtp_test(void)
//{  
//	while(1)
//	{
//		tp_dev.scan(0); 		 
//		if(tp_dev.sta&TP_PRES_DOWN)			//������������
//		{	
//		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
//			{	
//				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//���
//				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//��ͼ	  			   
//			}
//		}else delay_ms(10);	//û�а������µ�ʱ�� 	    
//	}
//}

int main(void)
{				 
 
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	W25QXX_Init();				//��ʼ��W25Q128 ��SPI2
	tp_dev.init();			//��������ʼ�� 
	while(font_init()) 			//����ֿ�
	{;}  
	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	Show_Str(5,5,132,24,"��һ�����ݣ�",24,0);
	Show_Str(5,35,132,24,"�ڶ������ݣ�",24,0);
	Show_Str(5,65,108,24,"�¶����ݣ�",24,0);
//		LCD_DrawRectangle(10,10,150,80);
//		LCD_ShowString(11,11,80,16,16,"right");
//		LCD_DrawRectangle(10,100,150,170);
//		LCD_ShowString(11,101,64,16,16,"left");
//		Show_Str(150,200,48,24,"У׼",24,0);
  	while(1)
	{
////		test_touch();
//		rtp_test(); 	
//LCD_ShowChar(60+40,150,' ',16,0);			//ȥ������
//			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//��ʾ��������	    
//   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//��ʾС������ 	
		temp_memory();
	}	 
} 






