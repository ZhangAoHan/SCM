#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "Motor.h"

int main(void)
{			
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	TIME3_PWM_init(0,7199);   //PWMƵ��Ϊ72M/7200=10Khz
	IO_init();
   	while(1)
	{
		Motor1Vcc=1;
		Motor1Gnd=0;
		Motor1=7000;
		
//		Motor2Vcc=0;
//		Motor2Gnd=1;
//		Motor2=7200;
	} 
}














