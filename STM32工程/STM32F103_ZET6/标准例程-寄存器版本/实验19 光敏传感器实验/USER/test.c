#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "adc.h"
#include "lsens.h"
//ALIENTEKս��STM32������ ʵ��19
//���������� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

int main(void)
{		 	
 	u8 adcx; 
  	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
  	LCD_Init();				//��ʼ��LCD
	Lsens_Init(); 			//��ʼ������������
	POINT_COLOR=RED;//��������Ϊ��ɫ  	
	//��ʾ��ʾ��Ϣ											      
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"LSENS TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/14");	  
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(30,130,200,16,16,"LSENS_VAL:");	             
	while(1)
	{
		adcx=Lsens_Get_Val();
		LCD_ShowxNum(30+10*8,130,adcx,3,16,0);//��ʾADC��ֵ 
		LED0=!LED0;
		delay_ms(250);	
	}
}


