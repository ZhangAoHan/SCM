#include "sys.h"
#include "usart.h"		
#include "delay.h"	   
#include "TFT.h"   
#include "ff.h"  
#include "exfuns.h"
#include "fontupd.h"
#include "text.h"	
#include "malloc.h" 
#include "MMC_SD.h" 
#include "AT24c02.h"  
#include "touch.h"  

void display(void)
{
	POINT_COLOR=RED;
	Show_Str(10,10,48,24,"��ʾ",24,1);
	LCD_ShowString(58,10,72,24,24,"ID:");
	POINT_COLOR=BLACK;
	Show_Str(130,10,24,24,"��",24,1);
	Show_Str(180,10,24,24,"��",24,1);
	Show_Str(10,296,72,24,"�Űº�",24,1);
}
int main(void)
{
	u8 key;
	u8 lcd_id[12]; //��� LCD ID �ַ���
	Stm32_Clock_Init(9); //ϵͳʱ������
	uart_init(72,115200); //���ڳ�ʼ��Ϊ 115200
	delay_init(72); //��ʱ��ʼ��
	LCD_Init();
 	mem_init();				//��ʼ���ڴ��
	exfuns_init();			//Ϊfatfs��ر��������ڴ�  
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//�� LCD ID ��ӡ�� lcd_id ���顣
		tp_dev.init();			//��������ʼ��
	while(font_init()) 	//����ֿ�
	{  
		key=update_font(20,110,16);//�����ֿ�
		while(key)//����ʧ��		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(RED);//����	       
	}
	LCD_Clear(WHITE);
		
	while(1)
	{
//		POINT_COLOR=BLACK;
//		LCD_ShowString(30,30,150,54,24,"STM32");   //X,Y,�����С���ֺ�*�ַ����� �ֺ�  �ַ�     ����240*320   �ַ�240*319
//		LCD_Fill(17,56,47,86,RED);
//		POINT_COLOR=BLUE;
//		LCD_Draw_Circle(32,71,15);
//		LCD_DrawRectangle(16,55,48,87);
//		//��ʾ����
//	    Show_Str(100,100,72,24,"�Űº�",24,1); 
		
//		LCD_ShowString(30,110,200,16,16,lcd_id);		//��ʾLCD ID
				display();
		tp_dev.scan(0);//��ⰴ���Ƿ񱻰���
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{
					if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{
		 	if(tp_dev.x[0]>127&&tp_dev.x[0]<157&&tp_dev.y[0]>7&&tp_dev.y[0]<37) LCD_ShowString(107,295,132,24,24,lcd_id);		//��ʾLCD ID;  
            if(tp_dev.x[0]>183&&tp_dev.x[0]<217&&tp_dev.y[0]>7&&tp_dev.y[0]<37) LCD_Clear(WHITE);			
		}

			
		
	}
	}
}


