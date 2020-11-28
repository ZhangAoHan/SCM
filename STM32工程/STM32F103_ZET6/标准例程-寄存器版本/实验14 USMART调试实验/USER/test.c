#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"
#include "usmart.h"
//ALIENTEKս��STM32������ʵ��14
//USMART������� ʵ��  
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
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	usmart_dev.init(72); 	//��ʼ��USMART				 	
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();				//��ʼ��LCD
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"WarShip STM32 ^_^");	
	LCD_ShowString(30,70,200,16,16,"USMART TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/14");	   
  	while(1) 
	{		 	  
		LED0=!LED0;					 
		delay_ms(500);	
	}
}























