#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "timer.h"
#include "C.h"
u32 Distance;                               //���������
void Dj(void);
int main(void)
{				 
//	u8 t=0; 
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600
	PWM_Init(200,7199);      //���������Ҫ20ms�����弴50HZ    50=72 000 000/psc*arr  
	
	TIM2_Init(65535,71);
  	while(1)
	{
		Read_Distane();
		printf("Distance:%d\r\n",Distance);
	Dj();

	}	 
} 


void Dj()
{	
	PWM=12;    //��ֵ
	delay_ms(1000);
	 PWM=9;    //ƫ25������
	delay_ms(1000);
		PWM=12;    //��ֵ
	delay_ms(1000);
	 PWM=15;    //ƫ25������
	delay_ms(1000);
}



