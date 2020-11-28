#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "key.h" 
#include "usmart.h" 
#include "malloc.h"  
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h"
//ALIENTEK Mini STM32开发板范例代码29
//FATFS 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  
    							   	 
int main(void)
{		 
 	u32 total,free;
	u8 t=0;		   	    
  	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化  	  
 	exfuns_init();		//为fatfs相关变量申请内存				 
	LCD_Init();			//初始化液晶 
	LED_Init();         //LED初始化	 													    
	usmart_dev.init(72);	
 	mem_init();			//初始化内存池	

 	POINT_COLOR=RED;//设置字体为红色	   
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"FATFS TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"Use USMART for test");	  
	LCD_ShowString(60,130,200,16,16,"2014/3/14");	  

	while(SD_Initialize())					//检测SD卡
	{
		LCD_ShowString(60,150,200,16,16,"SD Card Error!");
		delay_ms(200);
		LCD_Fill(60,150,240,150+16,WHITE);//清除显示			  
		delay_ms(200);
		LED0=!LED0;//DS0闪烁
	}								   	
 	exfuns_init();							//为fatfs相关变量申请内存				 
  	f_mount(fs[0],"0:",1); 					//挂载SD卡 
 	f_mount(fs[1],"1:",1); 					//挂载FLASH.	  
	while(exf_getfree("0",&total,&free))	//得到SD卡的总容量和剩余容量
	{
		LCD_ShowString(60,150,200,16,16,"Fatfs Error!");
		delay_ms(200);
		LCD_Fill(60,150,240,150+16,WHITE);//清除显示			  
		delay_ms(200);
		LED0=!LED0;//DS0闪烁
	}													 
 	POINT_COLOR=BLUE;//设置字体为蓝色	   
	LCD_ShowString(60,150,200,16,16,"FATFS OK!");	 
	LCD_ShowString(60,170,200,16,16,"SD Total Size:     MB");	 
	LCD_ShowString(60,190,200,16,16,"SD  Free Size:     MB"); 	    
 	LCD_ShowNum(172,170,total>>10,5,16);					//显示SD卡总容量 MB
 	LCD_ShowNum(172,190,free>>10,5,16);						//显示SD卡剩余容量 MB			    
	while(1)
	{
		t++;
		delay_ms(200);		 			   
		LED0=!LED0;
	} 
}













