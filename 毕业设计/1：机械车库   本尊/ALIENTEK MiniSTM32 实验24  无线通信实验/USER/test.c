#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "24l01.h" 
#include "control.h"
#include "motor.h"
#include "timer.h"
#include "motor.h"
#include "io_control.h"
u8 tmp_buf[33]; 
 u8 lc;  //¥����
 u8 start;  

int main(void)
{		
			 

 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
// 	NRF24L01_Init();    	//��ʼ��NRF24L01  	
	

	PWM_Init(999,0);   //pwm��ֵ=7200��Ƶ��=10K
	TIM3_Int_Init(4999,7199);
	Io_init();
// 	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
//	{;}	
	DJ_PWM_Init(200,7199);       //���ƶ��
	NRF24L01_RX_Mode();		
//	user_motor_init();
	
while(1)
{

	use_control();
	
}
	
}



















