#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "oled.h" 
//ALIENTEK Mini STM32�����巶������10
//OLED��ʾʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 
int main(void)
{			 
 	u8 t=0;	    	
 	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);	    //��ʱ��ʼ��
	uart_init(72,9600); //���ڳ�ʼ�� 
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ� 
	OLED_Init();		//��ʼ��OLED
  	OLED_ShowString(0,0,"ALIENTEK",24);  
	OLED_ShowString(0,24, "0.96' OLED TEST",16);  
 	OLED_ShowString(0,40,"ATOM 2014/3/7",12);  
 	OLED_ShowString(0,52,"ASCII:",12);  
 	OLED_ShowString(64,52,"CODE:",12);  
	OLED_Refresh_Gram();//������ʾ��OLED	 
	t=' ';  
	while(1) 
	{		
		OLED_ShowChar(36,52,t,12,1);//��ʾASCII�ַ�	
		OLED_ShowNum(94,52,t,3,12);	//��ʾASCII�ַ�����ֵ    
		OLED_Refresh_Gram();//������ʾ��OLED
		t++;
		if(t>'~')t=' ';  
		delay_ms(500);
		LED0=!LED0;
	}	  
}











