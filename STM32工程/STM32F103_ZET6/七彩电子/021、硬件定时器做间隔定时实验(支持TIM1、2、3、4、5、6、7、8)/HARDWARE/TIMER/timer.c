#include "timer.h"
#include "led.h"





/*************************** �ļ�˵�� *******************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 






//�ȿ���һ��
/* 

103�Ķ�ʱ����Ϊ3��

�߼����ƶ�ʱ��:  TIM1 TIM8           (ʱ����Դ��APB2 * 1 , ���72M * 1 =72M )
ͨ�ö�ʱ��    :  TIM2 TIM3 TIM4 TIM5 (ʱ����Դ��APB1 * 2 , ���36M * 2 =72M )
������ʱ��    :  TIM6 TIM7           (ʱ����Դ��APB1 * 2 , ���36M * 2 =72M )

�������е�F103��Ƭ����ӵ��ȫ����ʱ��

STM32F103C8         TIM1 TIM2 TIM3 TIM4 
STM32F103RC������   TIM1 TIM2 TIM3 TIM4 TIM5 TIM6 TIM7 TIM8
STM32F103xF������   TIM1 TIM2 TIM3 TIM4 TIM5 TIM6 TIM7 TIM8 TIM9 TIM10 TIM11 TIM12 TIM13 TIM14

*/



TIM_TypeDef * TIM[]={TIM1,TIM2,TIM3,TIM4,TIM5,TIM6,TIM7,TIM8};
u8 TIM_IRQChannel[]={TIM1_UP_IRQn,TIM2_IRQn,TIM3_IRQn,TIM4_IRQn,TIM5_IRQn,TIM6_IRQn,TIM7_IRQn,TIM8_UP_IRQn};





/*
����: ����΢��ʱ���ʼ����ʱ��Ϊ�����ʱ���������ж�
TIM_Index: ��ӦӲ����ʱ�������,ֻ֧��1~8,9~14ֻ��103xF��xGϵ�в���,δ��֧��
nus : Ҫ��ʼ�������ʱ���ļ�� ,��λΪus,����1000��Ϊ1ms�ж�һ��,���֧��65535us,��65.535ms
����ֵ: ��
*/
void TIM_SetInterval(u8 TIM_Index,u32 nus){
	
	if(nus==0){
		return ;
	}
	TIM_Init(TIM_Index,72-1,nus-1);
}



/*
����: ���ݷ�Ƶϵ���ͼ������ֵ��ʼ����ʱ��Ϊ�����ʱ���������ж�
TIM_Index: ��ӦӲ����ʱ�������,ֻ֧��1~8,9~14ֻ��103xF��xGϵ�в���,δ��֧��
nus : Ҫ��ʼ�������ʱ���ļ�� ,��λΪus,����1000��Ϊ1ms�ж�һ��,���֧��65535us,��65.535ms
����ֵ: ��
*/
void TIM_Init(u8 TIM_Index,u16 Prescaler,u16 Period){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	if(TIM_Index>=2&&TIM_Index<=7){//TIM2 ~ TIM7
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2<<(TIM_Index-2), ENABLE); //ʱ��ʹ��
	}
	else if(TIM_Index==1){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��
	}
	else if(TIM_Index==8){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //ʱ��ʹ��
	}
	else {
		return ;//�����Ĳ�֧��
	}
		
	
	//��ʱ����ʼ��
		
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period = Period; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//
	TIM_TimeBaseInit(TIM[TIM_Index-1], &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM[TIM_Index-1],TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM�ж�,��������ж�

	
	TIM_ARRPreloadConfig(TIM[TIM_Index-1],DISABLE);
	
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQChannel[TIM_Index-1];  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM[TIM_Index-1], ENABLE);  //ʹ��TIMx		
}



#if 0
//��ʱ���жϷ������
void TIM1_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			//LED1=!LED1;
		}
}
#endif



#if 1
//��ʱ���жϷ������
void TIM2_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			//LED1=!LED1;
		}
}
#endif



#if 1
//��ʱ���жϷ������
void TIM3_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			//LED1=!LED1;
		}
}
#endif



#if 1
//��ʱ���жϷ������
void TIM4_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			//LED1=!LED1;
		}
}
#endif



#if 1
//��ʱ���жϷ������
void TIM5_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			//LED1=!LED1;
		}
}
#endif



#if 1
//��ʱ���жϷ������
void TIM6_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			//LED1=!LED1;
		}
}
#endif



#if 1
//��ʱ���жϷ������
void TIM7_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			//LED1=!LED1;
		}
}
#endif



#if 1
//��ʱ���жϷ������
void TIM8_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM8, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			//LED1=!LED1;
		}
}
#endif

























