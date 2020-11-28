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

int main(void)
{
	u8 key;
	
	Stm32_Clock_Init(9); //系统时钟设置
	uart_init(72,115200); //串口初始化为 115200
	delay_init(72); //延时初始化
	LCD_Init();
 	mem_init();				//初始化内存池
	exfuns_init();			//为fatfs相关变量申请内存  
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


			
		
	
	}
}


