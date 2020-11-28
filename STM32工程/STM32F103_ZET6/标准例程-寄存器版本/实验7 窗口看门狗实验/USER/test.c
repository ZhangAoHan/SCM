#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "key.h"
#include "wdg.h" 	  
//ALIENTEKս��STM32������ʵ��7
//���ڿ��Ź� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
int main(void)
{					   
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
	KEY_Init();         	//��ʼ���밴�����ӵ�Ӳ���ӿ�
 	LED0=0;				 	//����DS0
	delay_ms(300);			//��ʱ300ms,���˿��Կ���DS0����״̬
 	WWDG_Init(0X7F,0X5F,3);	//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	   
 	while(1)
	{
		LED0=1;			  	 //��DS1
	}  		 
}

