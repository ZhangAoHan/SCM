/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "rtc.h"



/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
 


int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	USART1_Init(115200);//����1��ʼ��
	
	
	while(RTC_Init())//RTC��ʼ��
	{
		delay_ms(500);
		delay_ms(500);
		LED_TOGGLE(LED0);
		LED_TOGGLE(LED1);
		printf("RTC Init Failed!\r\n");
	}
	
	printf("RTC Init OK !\r\n");
	
	//RTC_Set(2017,12,4,12,4,30);//����ʱ��		
	
	
	while(1)
	{
		
		printf("Time:%d-%d-%d %d:%02d:%02d\r\n",\
					calendar.w_year,\
					calendar.w_month,\
					calendar.w_date,\
					calendar.hour,\
					calendar.min,\
					calendar.sec);//���ʱ��
		
		delay_ms(1000);
		LED_TOGGLE(LED1);
	}
}




