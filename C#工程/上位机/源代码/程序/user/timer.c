/*------------------------------------------------------------------------
	STM32ͨ�ö�ʱ��2,3,4,5,8���ó���
	
	˵��: 1) ��ʱ��ʱ��Ƶ��(Hz)=72MHZ/(ʱ��Ԥ��Ƶ+1)
		     ��CK_CNT=72000000/(TIM_Prescaler+1)
		     �����ж�ʱ��(s)=(TIM_Prescaler+1)*(TIM_Period+1)/CK_INT
		     CK_INTĬ��Ϊ72000000Hz 
		     ���ο��ֲ�263ҳ

		  2) ��ʱ��ʹ�����һ��
		  	 TIM1 - δʹ��
		  	 TIM2 - TRGO�¼�����DAC1ת��
			 TIM3 - TRGO�¼�����ADC1ת��
			 TIM4 - δʹ��
			 TIM5 - ����Ƶ��1MHz,����������Ƶ��
			 TIM6 - δʹ��
			 TIM7 - δʹ��
			 TIM8 - δʹ��

	ʱ��: 2013��7��26�� BoX��д
-----------------------------------------------------------------------*/
#include "timer.h"
#include "stm32f10x.h"
#include "pincfg.h"
#include "ucos_ii.h"
/*-----------------------------------------
		    	��������
------------------------------------------*/
extern u32  IntFullTime; //�������β�TIM5�ж��������
/*-----------------------------------------------
	��������: TIM5�ж����ʱ������
	��������: ARR/10�Ĵ���ֵ0-6553ms
-----------------------------------------------*/
void TIM5_Set_Time(unsigned short int Auto_Reload)
{
	TIM5_Config((Auto_Reload*10)-1,72);  //72ΪԤ��Ƶϵ��,�������趨
	TIM_Cmd(TIM5,ENABLE);    			 //ʹ��TIM5
}
/*-----------------------------------------------
	��������: TIM5��ʱ��Ϊ���������ṩ��ʱ
	��������: ARR�Ĵ���ֵ0-65535,Ԥ��Ƶֵ0-65535
    �� �� ֵ: TIM5_Config(1999,71)
	          ����Ƶ��1MHz,�ж�Ƶ��500Hz
			  ������ÿ1us��1,�ж�ÿ2ms����һ��		  			  
-----------------------------------------------*/
void TIM5_Config(unsigned short int Period,unsigned short int Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	
	//����TIM5
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler; 			//ʱ��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseStructure.TIM_Period = Period;			        //�Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //ʱ�ӷ�Ƶ1
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);  					
	//����TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	    //��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	            
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM5,ENABLE); 	
}
/*-----------------------------------------------
	��������: TIM4��ʱ��Ϊ����ռ�ձ��ṩ��ʱ
	��������: ARR�Ĵ���ֵ0-65535,Ԥ��Ƶֵ0-65535
    �� �� ֵ: TIM5_Config(59999,71)
	          ����Ƶ��1MHz,�ж�Ƶ��16.6Hz
			  ������ÿ1us��1,�ж�ÿ60ms����һ��		  			  
-----------------------------------------------*/
void TIM4_Config(unsigned short int Period,unsigned short int Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
	//����TIM5
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler; 			//ʱ��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseStructure.TIM_Period = Period;			        //�Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //ʱ�ӷ�Ƶ1
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

	TIM_Cmd(TIM4,ENABLE); 	
}
/*-----------------------------------------------
 ��������:TIM5�жϷ������
 ����˵��:���ж��м�¼TIM5���������������
          ��oscilloscope.c������ж��������������
-----------------------------------------------*/
void TIM5_IRQHandler(void)
{
	OSIntNesting++;							    //�����ж�֪ͨUCOS
	IntFullTime++;								//���������1  		                      
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����ж�
	OSIntExit(); 
}
	