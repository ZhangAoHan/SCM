#include "sys.h" 	
#include "delay.h"	
#include "led.h"
//ALIENTEKս��STM32������ ʵ��1
//����� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
int main(void)
{				  
	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);	  	//��ʱ��ʼ��
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(300);
		LED0=1;
		LED1=0;
		delay_ms(300);
	}	 
}

