#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "oled.h"
#include "ds.h"

void Display(void);
void Temp(void);
short temperature;
short a=0,b=0;
 int main(void)
 {	
	   
	delay_init(72);	    	 //延时函数初始化	 
	uart_init(72,9600); 	//串口初始化为9600	   
	LED_Init();		  	//初始化与LED连接的硬件接口
	OLED_Init();
	OLED_Clear();

	while(1)
	{
		Temp();
		Display();
		if(a>=28)
		{
			FS=0;
			BEEP=0;
			LED1=1;
			LED2=0;
		}
		else
		{
			FS=1;
			BEEP=1;
			LED2=1;
			LED1=0;
		}
		}
 }

void Display()
{
	OLED_ShowCHinese(0,0,0);
	OLED_ShowCHinese(16,0,1);
	OLED_ShowString(0,2,"T=",16);
	OLED_ShowChar(16,2,':',16);
	OLED_ShowNum(24,2,a,3,16);
	OLED_ShowChar(48,2,'.',16);
	OLED_ShowNum(56,2,b,1,16);
}

void Temp()
{
	temperature=DS18B20_Get_Temp();	
	a=temperature/10;
	b=temperature%10;

	
}

