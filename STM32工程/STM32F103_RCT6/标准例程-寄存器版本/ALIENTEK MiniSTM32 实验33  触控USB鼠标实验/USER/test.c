#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "key.h"  
#include "24cxx.h"  
#include "touch.h"  
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h" 
//ALIENTEK Mini STM32开发板范例代码33
//触控USB鼠标实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  
 
//装载画图界面						
void Load_Draw_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色 
}	  
//计算x1,x2的绝对值
u32 usb_abs(u32 x1,u32 x2)
{
	if(x1>x2)return x1-x2;
	else return x2-x1;
} 	  
int main(void)
{		
	u8 key;
	u8 i=0;
 	s8 x0;		 	//发送到电脑端的坐标值
	s8 y0;
	u8 keysta;		//[0]:0,左键松开;1,左键按下;
					//[1]:0,右键松开;1,右键按下
					//[2]:0,中键松开;1,中键按下
	u8 tpsta=0;		//0,触摸屏第一次按下;1,触摸屏滑动	   
	short xlast; 	//最后一次按下的坐标值
	short ylast;			   
   	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化  	  
	LCD_Init();			//初始化液晶 
	LED_Init();         //LED初始化	 
	KEY_Init();			//按键初始化	  													    
	TP_Init();			//初始化触摸屏  
	POINT_COLOR=RED;      						    	   
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"USB Mouse TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/15");	
	LCD_ShowString(60,130,200,16,16,"KEY_UP:SCROLL +");		 
	LCD_ShowString(60,150,200,16,16,"KEY1:RIGHT BTN");	
	LCD_ShowString(60,170,200,16,16,"KEY0:LEFT BTN");	
  	delay_ms(1800);
 	USB_Port_Set(0); 	//USB先断开
	delay_ms(300);
   	USB_Port_Set(1);	//USB再次连接
	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	        
	Load_Draw_Dialog();    
 	while(1)
	{	  
		key=KEY_Scan(1);//支持连按
		if(key)
		{								    	 
			if(key==3)Joystick_Send(0,0,0,1); 		//发送滚轮数据到电脑    
			else 
			{
				if(key==1)keysta|=0X01;		 		//发送鼠标左键    
				if(key==2)keysta|=0X02;		   		//发送鼠标右键
				Joystick_Send(keysta,0,0,0);		//发送给电脑
			}			    	 
		}else if(keysta)//之前有按下
		{
			keysta=0;
			Joystick_Send(0,0,0,0); //发送松开命令给电脑
		} 
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)	//触摸屏被按下
		{
			//最少移动5个单位,才算滑动
  			if(((usb_abs(tp_dev.x[0],xlast)>4)||(usb_abs(tp_dev.y[0],ylast)>4))&&tpsta==0)//等待滑动
			{
				xlast=tp_dev.x[0];		//记录刚按下的坐标 
				ylast=tp_dev.y[0];
	 			tpsta=1;
			}
 			if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Draw_Dialog();//清除
				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//画图	  
				if(bDeviceState==CONFIGURED)
				{   
					if(tpsta)//滑动
					{
						x0=(xlast-tp_dev.x[0])*3;	//上次坐标值与得到的坐标值之差,扩大2倍
						y0=(ylast-tp_dev.y[0])*3;
						xlast=tp_dev.x[0];			//记录刚按下的坐标 
						ylast=tp_dev.y[0];
						Joystick_Send(keysta,-x0,-y0,0); //发送数据到电脑  
						delay_ms(5);	   
					}       
				}				   
			}
		}else 
		{	
			tpsta=0;	//清除 
 			delay_ms(1);
		}
		if(bDeviceState==CONFIGURED)LED1=0;//当USB配置成功了，LED1亮，否则，灭
		else LED1=1;    
		i++;
		if(i==200)
		{
			i=0;
			LED0=!LED0;
		}
	}	   										    			    
}


