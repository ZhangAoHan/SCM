#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "beep.h" 
#include "key.h"	 	 
//ALIENTEKս��STM32������ʵ��4
//���� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

u8 res=0x00;	
int main(void)
{								  

	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ� 
	LED0=0;
 	while(1)
	{
		switch(res)
		{
			case 0x01:LED0=1;break;
			case 0x02:LED0=0;break;
		}
	}		 
}

