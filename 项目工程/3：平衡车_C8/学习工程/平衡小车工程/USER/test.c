#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "Motor.h"	
#include "Oled.h"	

int main(void)
{

	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600

	PWM_Init(7199,0);    //������ƺ�����PWM��ֵΪ7200��Ƶ��Ϊ10k��
	Motor_Init();
	
  	while(1)
	{

	}	 
} 






