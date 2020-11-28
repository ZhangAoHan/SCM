#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "beep.h"
#include "exti.h" 	 
//ALIENTEKս��STM32������ʵ��5
//�ⲿ�ж� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
int main(void)
{					   
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ� 
	BEEP_Init();		 	//��ʼ��������IO
	EXTIX_Init();         	//��ʼ���ⲿ�ж����� 
	LED0=0;					//�ȵ������
	while(1)
	{	    
		printf("OK\r\n");	
		delay_ms(1000);	  
	}	 
}

