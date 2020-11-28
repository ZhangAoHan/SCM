#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "wkup.h" 
//ALIENTEK Mini STM32�����巶������14
//��������ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
int main(void)
{			   
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	WKUP_Init();			//��ʼ��WK_UP������ͬʱ����Ƿ�����������
	LCD_Init();			   	//��ʼ��LCD 			 	
 	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"Mini STM32");	
	LCD_ShowString(30,70,200,16,16,"WKUP TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/3/8");	 
	while(1)
	{
		LED0=!LED0;
		delay_ms(250);
	}											    
}	









