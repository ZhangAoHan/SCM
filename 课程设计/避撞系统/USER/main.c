#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "oled.h"
#include "csb.h"   
u32 Distance;  
float m1,m2;
void Display(void);
 int main(void)
 {	
	delay_init(72);	    	 //延时函数初始化	 
	uart_init(72,9600); 	//串口初始化为9600	   
	LED_Init();		  	//初始化与LED连接的硬件接口
	OLED_Init();
	OLED_Clear();
	 TIM3_Cap_Init(0XFFFF,72-1);	
	while(1)
	{
    Read_Distane();	     
	m1=Distance/10;
	m2=Distance%10;	
	if(m1>3000)
	{
		m1=0;
	}
	if(m1<5)
	{
		Beep=0;
	}
	if(m1>=5)
	{
		Beep=1;
	}
		Display();

	}
 }

void Display()
{
	OLED_ShowCHinese(0,0,0);
	OLED_ShowCHinese(16,0,1);
	OLED_ShowChar(32,0,':',16);
	OLED_ShowNum(40,0,m1,4,16);
	OLED_ShowChar(72,0,'.',16);
	OLED_ShowNum(80,0,m2,1,16);
	OLED_ShowString(88,0,"CM",16); 
	OLED_ShowCHinese(0,2,5);
	OLED_ShowCHinese(16,2,6);
	OLED_ShowNum(32,2,141,3,16);
}



