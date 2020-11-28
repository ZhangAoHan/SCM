#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "wkup.h" 
//ALIENTEKս��STM32������ ʵ��16
//�������� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

int main(void)
{		 	   			    
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	WKUP_Init();			//��ʼ��WK_UP������ͬʱ����Ƿ�����������
 	LCD_Init();				//��ʼ��LCD
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"Warship STM32");	
	LCD_ShowString(30,70,200,16,16,"WKUP TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/14");	 
	while(1)
	{
		LED0=!LED0;
		delay_ms(250);
	}
}









