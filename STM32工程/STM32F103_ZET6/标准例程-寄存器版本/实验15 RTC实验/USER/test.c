#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"
#include "usmart.h"
#include "rtc.h" 
//ALIENTEKս��STM32������ ʵ��15
//RTCʵʱʱ�� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

int main(void)
{		
	u8 t;		   			    
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	usmart_dev.init(72);	//��ʼ��USMART				 	
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();				//��ʼ��LCD
	POINT_COLOR=RED;		//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32F103 ^_^");	
	LCD_ShowString(30,70,200,16,16,"RTC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/14");	
	while(RTC_Init())		//RTC��ʼ��	��һ��Ҫ��ʼ���ɹ�
	{ 
		LCD_ShowString(30,130,200,16,16,"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(30,130,200,16,16,"RTC Trying...");	
	}		    						
	//��ʾʱ��
	POINT_COLOR=BLUE;//��������Ϊ��ɫ					 
	LCD_ShowString(30,130,200,16,16,"    -  -     ");	   
	LCD_ShowString(30,166,200,16,16,"  :  :  ");	 		    
	while(1)
	{								    
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowNum(30,130,calendar.w_year,4,16);									  
			LCD_ShowNum(70,130,calendar.w_month,2,16);									  
			LCD_ShowNum(94,130,calendar.w_date,2,16);	 
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(30,148,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(30,148,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(30,148,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(30,148,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(30,148,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(30,148,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(30,148,200,16,16,"Saturday ");
					break;  
			}
			LCD_ShowNum(30,166,calendar.hour,2,16);									  
			LCD_ShowNum(54,166,calendar.min,2,16);									  
			LCD_ShowNum(78,166,calendar.sec,2,16);
			LED0=!LED0;
		}	
		delay_ms(10);								  
	};  
}











