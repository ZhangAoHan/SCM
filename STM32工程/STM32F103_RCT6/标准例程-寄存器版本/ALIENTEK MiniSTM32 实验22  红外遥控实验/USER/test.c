#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "remote.h"   
//ALIENTEK Mini STM32开发板范例代码22
//红外遥控实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

int main(void)
{		
	u8 key;
	u8 t=0;	
	u8 *str=0; 
 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 	
	Remote_Init();			//红外接收初始化	 
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"REMOTE TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/12");

   	LCD_ShowString(60,130,200,16,16,"KEYVAL:");	
   	LCD_ShowString(60,150,200,16,16,"KEYCNT:");	
   	LCD_ShowString(60,170,200,16,16,"SYMBOL:");	  		 	  		    							  
	while(1)
	{
		key=Remote_Scan();	
		if(key)
		{	 
			LCD_ShowNum(116,130,key,3,16);		//显示键值
			LCD_ShowNum(116,150,RmtCnt,3,16);	//显示按键次数		  
			switch(key)
			{
				case 0:str="ERROR";break;			   
				case 162:str="POWER";break;	    
				case 98:str="UP";break;	    
				case 2:str="PLAY";break;		 
				case 226:str="ALIENTEK";break;		  
				case 194:str="RIGHT";break;	   
				case 34:str="LEFT";break;		  
				case 224:str="VOL-";break;		  
				case 168:str="DOWN";break;		   
				case 144:str="VOL+";break;		    
				case 104:str="1";break;		  
				case 152:str="2";break;	   
				case 176:str="3";break;	    
				case 48:str="4";break;		    
				case 24:str="5";break;		    
				case 122:str="6";break;		  
				case 16:str="7";break;			   					
				case 56:str="8";break;	 
				case 90:str="9";break;
				case 66:str="0";break;
				case 82:str="DELETE";break;		 
			}
			LCD_Fill(116,170,116+8*8,170+16,WHITE);	//清楚之前的显示
			LCD_ShowString(116,170,200,16,16,str);	//显示SYMBOL
		}else delay_ms(10);	  
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}



















