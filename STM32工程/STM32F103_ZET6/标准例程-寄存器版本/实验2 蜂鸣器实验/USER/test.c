#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "beep.h" 	 
//ALIENTEKս��STM32������ʵ��2
//������ ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
int main(void)
{				  
	Stm32_Clock_Init(9); 	//ϵͳʱ������
	delay_init(72);	    	//��ʱ��ʼ��
	LED_Init();		  	 	//��ʼ����LED���ӵ�Ӳ���ӿ�
	BEEP_Init();         	//��ʼ���������˿�
	while(1)
	{
		LED0=0;				//����DS0
		BEEP=0;		  		//�رշ�����
		delay_ms(300);
		LED0=1;	  			//�ر�DS0
		BEEP=1;  			//�򿪷�����
		delay_ms(300);
	}	 
}








