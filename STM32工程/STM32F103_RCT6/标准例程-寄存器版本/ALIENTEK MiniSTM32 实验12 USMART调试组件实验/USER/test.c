#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h" 
#include "usmart.h" 
//ALIENTEK Mini STM32�����巶������12
//USMART�������ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 
//LED״̬���ú���
void led_set(u8 sta)
{
	LED1=sta;
} 
//�����������ò��Ժ���
void test_fun(void(*ledset)(u8),u8 sta)
{
	ledset(sta);
}  	
int main(void)
{			   
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);			//��ʱ��ʼ��
	uart_init(72,9600); 	//����1��ʼ��Ϊ9600
	LED_Init();				//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();				//��ʼ��LCD
	usmart_dev.init(72); 	//��ʼ��USMART				 	
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"Mini STM32 ^_^");	
	LCD_ShowString(30,70,200,16,16,"USMART TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/3/8");	   
  	while(1) 
	{		 	  
		LED0=!LED0;					 
		delay_ms(500);	
	}											    
}	









