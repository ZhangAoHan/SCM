#include "timer.h"
#include "delay.h"
#include "usart.h"

extern MOTOR GmLeft;//���岢��ʼ������״̬
extern MOTOR GmRight ;//���岢��ʼ���ҵ��״̬

void Timer2_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
 	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel =  TIM2_IRQn;  //TIM2�ж�	 TIM3_IRQn |
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0 ;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);

	
}
void TIM2_IRQHandler(void) 
{	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
	
		   
			switch (GmLeft.cState)
			{
				case MOTOR_STOP:						 /*	ֹͣ��ͬʱ�������� */
					GmLeft.ulPulse     =     0;
					GmLeft.ulPulseCtr  =     0;
					 break;

			    case MOTOR_RUN:
					 StepLeft();
					 break;

				default:
					 break;
			}

			/*
			*	�Ƿ���������ж�
			*/
			if(GmLeft.cState  ==  MOTOR_RUN)
			{
				GmLeft.ulPulseCtr++;
				if(GmLeft.ulPulseCtr  >=   GmLeft.ulPulse)
				{
					GmLeft.cState  =  MOTOR_STOP;
					GmLeft.ulPulseCtr =  0;
					GmLeft.ulPulse =  0;
				    //printf("ulPulseCtr = %d \n",GmRight.ulPulseCtr);
				}
			}
			
		}
}
/**/


/*
	�� �ܣ����Ʋ������
	�� �ã��ⲿ���� ���ڲ��������ʼ��������ʹ��
*/
void Timer3_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3 , //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);

	NVIC_Configuration(); 	 //����NVIC�жϷ���

	NVIC_InitStructure.NVIC_IRQChannel =  TIM3_IRQn;  //TIM3�ж�	 TIM3_IRQn |
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);

}

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ

			switch (GmRight.cState)
			{
				case MOTOR_STOP:						 /*	ֹͣ��ͬʱ�������� */
					GmRight.ulPulse     =     0;
					GmRight.ulPulseCtr  =     0;
					 break;

			    case MOTOR_RUN:
					 StepRight();
					 break;

				default:
					 break;
			}

			/*
			*	�Ƿ���������ж�
			*/
			if(GmRight.cState  ==  MOTOR_RUN)
			{
				GmRight.ulPulseCtr++;
				if(GmRight.ulPulseCtr  >=   GmRight.ulPulse)
				{
					GmRight.cState  =  MOTOR_STOP;
					GmRight.ulPulseCtr =  0;
					GmRight.ulPulse =  0;
				    //printf("ulPulseCtr = %d \n",GmRight.ulPulseCtr);
				}
			}
		}
}











