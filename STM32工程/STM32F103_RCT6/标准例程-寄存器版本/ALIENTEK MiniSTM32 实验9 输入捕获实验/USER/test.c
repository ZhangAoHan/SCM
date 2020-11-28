#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "timer.h" 
//ALIENTEK Mini STM32�����巶������9
//���벶��ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

extern u8  TIM2CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ
int main(void)
{			 
	u32 temp=0;  	
 	Stm32_Clock_Init(9);			//ϵͳʱ������
	uart_init(72,9600);	 			//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 			//��ʱ��ʼ�� 
	LED_Init();		  				//��ʼ����LED���ӵ�Ӳ���ӿ�
 	TIM1_PWM_Init(899,0); 			//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
 	TIM2_Cap_Init(0XFFFF,72-1);		//��1Mhz��Ƶ�ʼ��� 
   	while(1)
	{
 		delay_ms(10);
		LED0_PWM_VAL++;
		if(LED0_PWM_VAL==300)LED0_PWM_VAL=0;	 		 
		if(TIM2CH1_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
		{
			temp=TIM2CH1_CAPTURE_STA&0X3F;
			temp*=65536;					//���ʱ���ܺ�
			temp+=TIM2CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
			printf("HIGH:%d us\r\n",temp);	//��ӡ�ܵĸߵ�ƽʱ��
 			TIM2CH1_CAPTURE_STA=0;			//������һ�β���
 		}
	}
}











