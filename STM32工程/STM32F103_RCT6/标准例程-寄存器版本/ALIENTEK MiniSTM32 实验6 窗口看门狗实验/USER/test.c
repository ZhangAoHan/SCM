#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "wdg.h" 
//ALIENTEK Mini STM32�����巶������6
//���ڿ��Ź�ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

int main(void)
{			
  	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	LED0=0;
	delay_ms(300);	  
	WWDG_Init(0X7F,0X5F,3);//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	   
 	while(1)
	{
		LED0=1;			  	   
	}
}














