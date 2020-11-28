#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"  
#include "exti.h" 
//ALIENTEK Mini STM32�����巶������4
//�ⲿ�ж�ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

int main(void)
{			
	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);	    //��ʱ��ʼ��
	uart_init(72,9600); //���ڳ�ʼ�� 
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	EXTI_Init();		//�ⲿ�жϳ�ʼ��
	LED0=0;				//����LED
	while(1)
	{	    
		printf("OK\r\n");	
		delay_ms(1000);	  
	} 
}














