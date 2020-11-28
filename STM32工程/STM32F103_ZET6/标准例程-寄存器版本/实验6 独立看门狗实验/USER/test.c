#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "key.h"
#include "wdg.h" 	  
//ALIENTEKս��STM32������ʵ��6
//�������Ź� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
int main(void)
{					   
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
	KEY_Init();         	//��ʼ���밴�����ӵ�Ӳ���ӿ�
 	delay_ms(500);			//��ʱ500ms,���˿��Կ���DS0���״̬
 	IWDG_Init(4,625);    	//���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s	   
	LED0=0;				 	//����DS0
	while(1)
	{
		if(KEY_Scan(0)==WKUP_PRES)//���WK_UP����,��ι��
		{
			IWDG_Feed();
		}
		delay_ms(10);
	}		 
}

