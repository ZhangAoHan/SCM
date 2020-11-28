#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "motor.h"   
#include "laser.h"
#include "oled.h"
#include "sensor.h"
#include "ds18b20.h"
u8 Res=0x00;
u8 t1=0,t2=0;;  //��ʱ��������ÿ1s��1
int Temperature1,Temperature2,Candela;
u8 x,y;
u8 X=0;

void Go(void);
void Back(void);
void Stop(void);
void BlueTooth(void);
void Light_Time(u8 T);
void Display_init(void);
void Display_show(void);
void Laser(void);
void Measure(void);

 int main(void)
 {	
	uart_init(9600);	
	delay_init();	    	 //��ʱ������ʼ��	  
	TIM1_PWM_Init(899,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
	 TIM3_init(899,0); 
	Light_init();
	OLED_Init();
	OLED_Clear();
	Adc_Init(); //��ʼ������������
	 BEEP_Init();
	 Beep=1;
	 Display_init();
	 delay_ms(3000);
	 OLED_Clear();
	 	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
     OLED_ShowString(0,0,"DS18B20 Error",16);
	}
   	while(1)
	{
	     BlueTooth();
		 Laser();
		 Measure();
		 Display_show();
	} 
}
void Go(void)
{
		TIM_SetCompare1(TIM3,500);	 
		TIM_SetCompare2(TIM3,0);
}
void Back(void)
{
		TIM_SetCompare1(TIM3,0);	 
		TIM_SetCompare2(TIM3,500);
}
void Stop(void)
{
		TIM_SetCompare1(TIM3,0);	 
		TIM_SetCompare2(TIM3,0);
}
void Display_init(void)
{
	OLED_ShowCHinese(16,0,0);
	OLED_ShowCHinese(32,0,1);
	OLED_ShowCHinese(48,0,2);
	OLED_ShowCHinese(64,0,3);
	OLED_ShowCHinese(80,0,4);
	OLED_ShowCHinese(96,0,5);
	
	OLED_ShowCHinese(32,4,6);
	OLED_ShowCHinese(48,4,7);
	OLED_ShowCHinese(64,4,8);
}
void Display_show(void)
{
	OLED_ShowCHinese(0,0,9);    //�¶�
	OLED_ShowCHinese(16,0,10);
	OLED_ShowChar(32,0,':',16);
	OLED_ShowNum(48,0,Temperature1,2,16);
	OLED_ShowChar(64,0,'.',16);
	OLED_ShowNum(72,0,Temperature2,1,16);
	OLED_ShowChar(80,0,'C',16);
	
	OLED_ShowCHinese(0,2,13);    //��
	OLED_ShowCHinese(16,2,14);
	OLED_ShowChar(32,2,':',16);
	OLED_ShowCHinese(48,2,x);   //15 ��  16��
	
	OLED_ShowCHinese(0,4,17);    //����
	OLED_ShowCHinese(16,4,18);
	OLED_ShowChar(32,4,':',16);
    OLED_ShowCHinese(48,4,y);   //15 ��  16��
	
	OLED_ShowCHinese(0,6,11);    //��ǿ
	OLED_ShowCHinese(16,6,12);
	OLED_ShowChar(32,6,':',16);
	OLED_ShowNum(48,6,Candela,3,16);
	OLED_ShowString(72,6,"Cd",16);
}
void Laser(void)
{
	   if(Flame==0) x=15;else x=16;
	   if(Shock==0) y=15;else y=16;
	   if(x==15||y==15) Beep=0; else Beep=1;
}
void Measure(void)
{
	Candela=Get_Adc_Average(ADC_CH1,10);
	Candela=Candela/10;
	Temperature1=DS18B20_Get_Temp();
	Temperature2=Temperature1/10;
	Temperature1=Temperature1/10;
}

void BlueTooth(void)
{
	switch(Res)
	{
		case 0x00:Stop();break;
		case 0x01:Go(); break;    
		case 0x02:Back();break; 
		case 0x03:Light=0;break;
		case 0x04:Light=300; break;    
		case 0x05:Light=600;break; 
		case 0x06:Light=900;break;
		
	}
}
//void BlueTooth(void)
//{
//	switch(Res)
//	{
//		case 0x03:Stop();break;
//		case 0x01:Go(); break;    
//		case 0x02:Back();break; 
//	}
//}

