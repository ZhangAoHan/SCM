#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"   
#include "ds18b20.h"   
//ALIENTEK Mini STM32�����巶������23
//DS18B20�����¶ȴ�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

int main(void)
{		
	u8 t=0;			    
	short temperature;   
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD  
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"DS18B20 TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/12");		  
 	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	LCD_ShowString(60,130,200,16,16,"DS18B20 OK");
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
 	LCD_ShowString(60,150,200,16,16,"Temp:   . C");	 
	while(1)
	{	    	    
 		if(t%10==0)//ÿ100ms��ȡһ��
		{									  
			temperature=DS18B20_Get_Temp();	
			if(temperature<0)
			{
				LCD_ShowChar(60+40,150,'-',16,0);			//��ʾ����
				temperature=-temperature;					//תΪ����
			}else LCD_ShowChar(60+40,150,' ',16,0);			//ȥ������
			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//��ʾ��������	    
   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//��ʾС������ 		   
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}



















