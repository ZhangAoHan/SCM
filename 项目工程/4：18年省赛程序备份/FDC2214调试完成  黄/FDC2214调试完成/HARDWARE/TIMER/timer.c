#include "timer.h"
#include "sys.h"
#include "led.h"
#include "sys.h"


void TIM3_Config(uint16_t Period,uint16_t Prescaler,uint16_t Seize_priority,uint16_t Sub_priority)
{
	//����ṹ�����
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;		//���嶨ʱ��������ʼ���ṹ�����
	NVIC_InitTypeDef        NVIC_InitStructure;				//�����ж����ȼ����ýṹ�����
	//ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ��TIM3ʱ�ӣ�������APB1����
	//TIM3������ʼ��
	TIM_TimeBaseStructure.TIM_Period=Period;			//�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler=Prescaler;//����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	    //ʱ�ӷ�Ƶ1
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //TIM���ϼ���
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	//��ʼ��TIM3
	//ʹ�ܸ����жϲ������������жϱ�־λ
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//���TIM3�����жϱ�־λ
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//ʹ��TIM3�����ж�
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	//�����ʼ��ʱ�ĸ��ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=Seize_priority;//��ռ���ȼ�Ϊ0��������������ȼ���2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=Sub_priority;//�����ȼ�Ϊ0����ֵԽС���ȼ�Խ�ߣ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//IRQ��ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж����ȼ�NVIC
	//ʹ�������������TIM3
	TIM_Cmd(TIM3,ENABLE);//ʹ��TIM3
	
	
}


