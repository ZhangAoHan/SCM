#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "usart.h"
#include "Sensor.h"
#include "Led.h"
int Candela;
int Candela1;
u8 temperature;
u8 humidity;
u8 Res;
void display(void);
void Bluedisplay(u8 t1);
void BlueTooth(void);
 int main(void)
 {	
	 delay_init();	    	 //��ʱ������ʼ��	
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600	 
	 OLED_Init();			//��ʼ��OLED  
	 OLED_Clear(); 
	 Adc_Init(); //��ʼ������������
	 DHT11_Init();
	 TIM1_PWM_Init(1024,0);//PWMƵ��80Khz
		while(1)
		{
			Candela=Get_Adc_Average(ADC_CH1,10);
			DHT11_Read_Data(&temperature,&humidity);
			BlueTooth();			
			LED0_PWM_VAL=1024-Candela1/4;
			display();
		}

 }
void display(void)
{
		OLED_ShowCHinese(0,0,0);
	OLED_ShowCHinese(16,0,1);
	OLED_ShowChar(32,0,':',16);
	OLED_ShowNum(40,0,temperature,3,16);
	
		OLED_ShowCHinese(0,2,2);
	OLED_ShowCHinese(16,2,1);
	OLED_ShowChar(32,2,':',16);
	OLED_ShowNum(40,2,humidity,3,16);
	
		OLED_ShowCHinese(0,4,3);
	OLED_ShowCHinese(16,4,4);
	OLED_ShowChar(32,4,':',16);
	
}
void Bluedisplay(u8 t1)
{
	switch(t1)
	{
		case 0:OLED_ShowCHinese(0,6,15);OLED_ShowCHinese(16,6,16);OLED_ShowCHinese(32,6,17);OLED_ShowCHinese(48,6,18);break;
		case 1:OLED_ShowCHinese(0,6,19);OLED_ShowCHinese(16,6,16);OLED_ShowCHinese(32,6,17);OLED_ShowCHinese(48,6,18);break;
	}
}
void BlueTooth(void)
{
	switch(Res)
	{
		case 0x00:Candela1=Candela;Bluedisplay(0);OLED_ShowNum(40,4,Candela/4,4,16);break;
		case 0x01:
			Bluedisplay(1);
			Candela1=Candela1+300;
		if(Candela1>=4096)
		{Candela1=0;}
		OLED_ShowNum(40,4,Candela1/4,4,16);
		break;
	}
}

