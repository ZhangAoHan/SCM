#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "key.h" 
#include "24l01.h"   
//ALIENTEK Mini STM32开发板范例代码24
//无线通信实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

int main(void)
{		
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[33]; 
 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 	
 	KEY_Init();				//按键初始化
 	NRF24L01_Init();    	//初始化NRF24L01  
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"NRF24L01 TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/12");		  
 	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
		LCD_ShowString(60,130,200,16,16,"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	LCD_ShowString(60,130,200,16,16,"NRF24L01 OK");
 	while(1)//在该部分确定进入哪个模式!
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)
		{
			mode=0;   
			break;
		}else if(key==KEY1_PRES)
		{
			mode=1;
			break;
		}
		t++;
		if(t==100)LCD_ShowString(10,150,230,16,16,"KEY0:RX_Mode  KEY1:TX_Mode"); //闪烁显示提示信息
 		if(t==200)
		{	
			LCD_Fill(10,150,230,150+16,WHITE);
			t=0; 
		}
		delay_ms(5);	  
	}   
 	LCD_Fill(10,150,240,166,WHITE);//清空上面的显示		  
 	POINT_COLOR=BLUE;//设置字体为蓝色	   
	if(mode==0)//RX模式
	{
		LCD_ShowString(60,150,200,16,16,"NRF24L01 RX_Mode");	
		LCD_ShowString(60,170,200,16,16,"Received DATA:");	
		NRF24L01_RX_Mode();		  
		while(1)
		{	  		    		    				 
			if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
			{
				tmp_buf[32]=0;//加入字符串结束符
				LCD_ShowString(0,190,239,32,16,tmp_buf);    
			}else delay_us(100);	   
			t++;
			if(t==10000)//大约1s钟改变一次状态
			{
				t=0;
				LED0=!LED0;
			} 				    
		};	
	}else//TX模式
	{							    
		LCD_ShowString(60,150,200,16,16,"NRF24L01 TX_Mode");	
		NRF24L01_TX_Mode();
		mode=' ';//从空格键开始  
		while(1)
		{	  		   				 
			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				LCD_ShowString(60,170,239,32,16,"Sended DATA:");	
				LCD_ShowString(0,190,239,32,16,tmp_buf); 
				key=mode;
				for(t=0;t<32;t++)
				{
					key++;
					if(key>('~'))key=' ';
					tmp_buf[t]=key;	
				}
				mode++; 
				if(mode>'~')mode=' ';  	  
				tmp_buf[32]=0;//加入结束符		   
			}else
			{										   	
 				LCD_ShowString(60,170,239,32,16,"Send Failed "); 
				LCD_Fill(0,188,240,218,WHITE);//清空上面的显示			   
			};
			LED0=!LED0;
			delay_ms(1500);				    
		};
	} 
}



















