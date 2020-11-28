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
	Show_Str(10,10,48,24,"显示",24,1);
	LCD_ShowString(58,10,72,24,24,"ID:");
	POINT_COLOR=BLACK;
	Show_Str(130,10,24,24,"是",24,1);
	Show_Str(180,10,24,24,"否",24,1);
	Show_Str(10,296,72,24,"张奥涵",24,1);
}
int main(void)
{
	u8 key;
	u8 lcd_id[12]; //存放 LCD ID 字符串
	Stm32_Clock_Init(9); //系统时钟设置
	uart_init(72,115200); //串口初始化为 115200
	delay_init(72); //延时初始化
	LCD_Init();
 	mem_init();				//初始化内存池
	exfuns_init();			//为fatfs相关变量申请内存  
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将 LCD ID 打印到 lcd_id 数组。
		tp_dev.init();			//触摸屏初始化
	while(font_init()) 	//检查字库
	{  
		key=update_font(20,110,16);//更新字库
		while(key)//更新失败		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(RED);//清屏	       
	}
	LCD_Clear(WHITE);
		
	while(1)
	{
//		POINT_COLOR=BLACK;
//		LCD_ShowString(30,30,150,54,24,"STM32");   //X,Y,区域大小（字号*字符数） 字号  字符     汉字240*320   字符240*319
//		LCD_Fill(17,56,47,86,RED);
//		POINT_COLOR=BLUE;
//		LCD_Draw_Circle(32,71,15);
//		LCD_DrawRectangle(16,55,48,87);
//		//显示汉字
//	    Show_Str(100,100,72,24,"张奥涵",24,1); 
		
//		LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID
				display();
		tp_dev.scan(0);//检测按键是否被按下
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{
					if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{
		 	if(tp_dev.x[0]>127&&tp_dev.x[0]<157&&tp_dev.y[0]>7&&tp_dev.y[0]<37) LCD_ShowString(107,295,132,24,24,lcd_id);		//显示LCD ID;  
            if(tp_dev.x[0]>183&&tp_dev.x[0]<217&&tp_dev.y[0]>7&&tp_dev.y[0]<37) LCD_Clear(WHITE);			
		}

			
		
	}
	}
}


