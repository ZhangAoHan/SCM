#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "usmart.h" 
#include "sram.h"
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h" 
#include "vs10xx.h"
#include "mp3player.h"	
//ALIENTEK战舰STM32开发板 实验43
//音乐播放器 实验 
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 
int main(void)
{		 
 	Stm32_Clock_Init(9);		//系统时钟设置
	uart_init(72,115200);		//串口初始化为115200
	delay_init(72);	   	 		//延时初始化  
 	usmart_dev.init(72);		//初始化USMA RT		
 	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
	LCD_Init();			   		//初始化LCD     
	W25QXX_Init();				//初始化W25Q128
 	VS_Init();	  				//初始化VS1053 
 	my_mem_init(SRAMIN);		//初始化内部内存池
	exfuns_init();				//为fatfs相关变量申请内存  
 	f_mount(fs[0],"0:",1); 		//挂载SD卡 
 	f_mount(fs[1],"1:",1); 		//挂载FLASH.
	POINT_COLOR=RED;       
 	while(font_init()) 				//检查字库
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//清除显示	     
	}
 	Show_Str(30,50,200,16,"战舰 STM32开发板",16,0);				    	 
	Show_Str(30,70,200,16,"音乐播放器实验",16,0);				    	 
	Show_Str(30,90,200,16,"正点原子@ALIENTEK",16,0);				    	 
	Show_Str(30,110,200,16,"2015年1月20日",16,0);
	Show_Str(30,130,200,16,"KEY0:NEXT   KEY2:PREV",16,0);
	Show_Str(30,150,200,16,"KEY_UP:VOL+ KEY1:VOL-",16,0);
	while(1)
	{
  		LED1=0; 	  
		Show_Str(30,170,200,16,"存储器测试...",16,0);
		printf("Ram Test:0X%04X\r\n",VS_Ram_Test());//打印RAM测试结果	    
		Show_Str(30,170,200,16,"正弦波测试...",16,0); 	 	 
 		VS_Sine_Test();	   
		Show_Str(30,170,200,16,"<<音乐播放器>>",16,0); 		 
		LED1=1;
		mp3_play();
	} 	   										    
}










