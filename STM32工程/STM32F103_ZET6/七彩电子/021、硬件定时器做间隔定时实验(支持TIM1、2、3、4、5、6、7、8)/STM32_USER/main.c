/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"
#include "led.h"
#include "timer.h"


/*************************** �ļ�˵�� *******************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 


u32 timCnt=0;


#define INTERVAL_TIME  (1000)      //��ʱʱ��,��λms



int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Init(115200);//����1��ʼ��
	LED_Init();
	TIM_SetInterval(1,50000);//50ms
	
	while(1)
	{
		if(timCnt>=(INTERVAL_TIME/50)){//��ʱʱ�䵽
			timCnt=0;
			
			LED1=!LED1;
			
		}
	}
}




#if 1
//��ʱ���жϷ������
void TIM1_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET){  //���TIM�����жϷ������
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		//LED1=!LED1;
		if(timCnt<(INTERVAL_TIME/50)){
			timCnt++;
		}
	}
}
#endif






























