#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "oled.h"
#include "usart.h"	
u8 flag=0;
	u8 res=0x00;	
	u8 time=0;
		u8 time1=0;
	u8 FLAG=2;
	u8 T;
void GO(void);
void DOWN(void);
void BlueTooth(void);
void Display(u8 t);
 void display(void);
 int main(void)
 {	
	delay_init(72);	    	 //延时函数初始化	 
	uart_init(72,9600); 	//串口初始化为9600	 
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIME_init(1000,7200);   //每0.1s，标志变量取反一次
	 
	OLED_Init();
	OLED_Clear();
	 
	 
	OLED_ShowCHinese(0,0,2);
	OLED_ShowCHinese(16,0,3);
	OLED_ShowCHinese(32,0,4);
	 OLED_ShowCHinese(0,2,5);
	 OLED_ShowCHinese(16,2,6);
	 OLED_ShowNum(32,2,141,3,16);
	 OLED_ShowNum(0,4,2014131040,10,16);
	 delay_ms(2000); 
    OLED_Clear();	 
	while(1)
	{
		BlueTooth();	
////GO();	
//DOWN();		
	}
 }
 void display(void)
 {
	 OLED_ShowCHinese(0,0,2);
	 OLED_ShowCHinese(16,0,3);
	 OLED_ShowCHinese(32,0,4);
	 OLED_ShowCHinese(0,2,5);
	 OLED_ShowCHinese(16,2,6);
	 OLED_ShowNum(32,2,141,3,16);
	 OLED_ShowNum(0,4,2014131040,10,16);
 }
void Display(u8 t)
{
	switch(t)
	{
		case 0: OLED_ShowCHinese(48,2,13);OLED_ShowCHinese(64,2,0);OLED_ShowCHinese(0,6,2);OLED_ShowCHinese(16,6,3);OLED_ShowCHinese(32,6,4);break;           //停止
		case 1: OLED_ShowString(0,0,"Work",16);   OLED_ShowString(0,2,"Time",16);OLED_ShowChar(32,2,':',16); OLED_ShowNum(40,2,30-time,2,16);OLED_ShowCHinese(0,6,2);OLED_ShowCHinese(16,6,3);OLED_ShowCHinese(32,6,4);break;           //正转
		
	}
}
void BlueTooth(void)
{
	switch(res)
	{
		
		case 0x00:
			if(FLAG==1)
		{
			if(flag==0)
			{GO();}
			if(flag==1)
			{DOWN();}
			Display(1);
		}
		if(FLAG==0)
		{

			Go=0;
			Dowm=0;
		}
				if(FLAG==2)
		{

			Go=0;
			Dowm=0;
			Display(0);
		}
		break;  //停止
		case 0x01:time=0;OLED_Clear();FLAG=1;break;  //开始
		case 0x02:time1=time;OLED_Clear();FLAG=2;break;  //暂停（显示停止）
		case 0x03:time1=time; OLED_Clear();display();FLAG=0;break;  //停止
		case 0x04: time=time1;OLED_Clear();FLAG=1;break;  //恢复
		
	}
}
void GO(void)
{
		Go=1;
		Dowm=0;
		delay_ms(5);
		Go=0;
		Dowm=0;
		delay_ms(1);
}
void DOWN(void)
{
		Go=0;
		Dowm=1;
		delay_ms(5);
		Go=0;
		Dowm=0;
		delay_ms(1);
}

//0x00 工作  0x02 显示学号
