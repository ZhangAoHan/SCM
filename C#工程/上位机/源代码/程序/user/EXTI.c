/*-------------------------------------------------------------------------
       �ⲿIO���ж����ó���
 ˵��: EXTI_Config��������IO��ģʽ,�����һЩע�������Ѿ���ע����˵����
	   NVIC_Config���������ж�����������ȼ���,ע�������Ѿ���ע��˵����
 ����: �жϷ������д��stm32f10x_it.c��
	   �жϷ�������������д,ֻ�ܰ������ĸ��ж��߾�д�ĸ��涨���жϺ����� 
       ������жϺ������뵽startup_stm32f10x_hd.s�ļ���62��Ѱ����Ӧ�����֡�
	   �ж�����stm32f10x.h�ļ���188�п����ҵ������ж����б�,������Ҫѡ��
 ʱ��: 2013��7��22�� BoX��д 
--------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "EXTI.H"
#include "pincfg.h"
#include "ucos_ii.h"
#include "misc.h"
#include "task_main.h"
/*---------------------------------
			��������
----------------------------------*/
uint8_t InterruptTimes = 0;		 //�жϽ������
EXTI_InitTypeDef EXTI_IO_Init;	 //��Ҫ���жϸı䴥����,ֻ��ʹ��ȫ�ֱ���
extern WaveMode WaveCtrl;
extern WaveType WaveInfo;
/*---------------------------------------------------------------
	��������: �ⲿ�ж�����ģ��,����A0,A1��Ϊ�ⲿ�������ж� 
----------------------------------------------------------------*/
void EXTI_Config(void)
{
	GPIO_InitTypeDef IO_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	//����PA0,PA1Ϊ���������	
  	IO_Init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;				    
  	IO_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;		
  	GPIO_Init(GPIOA, &IO_Init);
	NVIC_Config(); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	EXTI_IO_Init.EXTI_Line = EXTI_Line0; 
	EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		//�ж�ģʽ
	EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Rising;    //�����ش����ж�
	EXTI_IO_Init.EXTI_LineCmd = ENABLE;				    //ʹ���ж�
	EXTI_Init(&EXTI_IO_Init);	 					    //д������
    
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); 
	EXTI_IO_Init.EXTI_Line = EXTI_Line1;
	EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		//�ж�ģʽ
	EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Rising;    //�����ش����ж�
	EXTI_IO_Init.EXTI_LineCmd = ENABLE;				    //ʹ���ж�
	EXTI_Init(&EXTI_IO_Init);	 					    //д������
}
/*---------------------------------------
	��������: Ƕ�������жϿ���������ģ�� 
---------------------------------------*/
static void NVIC_Config(void)
{
	NVIC_InitTypeDef NVICInit;
	NVICInit.NVIC_IRQChannel = EXTI0_IRQn;			 //0-4����IV,5-9����EXTI9_5_IRQn IV,10-15����EXTI15_10_IRQn IV	
	NVICInit.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2
    NVICInit.NVIC_IRQChannelSubPriority = 0;  		 //��Ӧ���ȼ�0
	NVICInit.NVIC_IRQChannelCmd = ENABLE;	         //ʹ���ж�
	NVIC_Init(&NVICInit);                            //д������
	
	NVICInit.NVIC_IRQChannel = EXTI1_IRQn;			 //0-4����IV,5-9����EXTI9_5_IRQn IV,10-15����EXTI15_10_IRQn IV	
	NVICInit.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1
    NVICInit.NVIC_IRQChannelSubPriority = 0;  		 //��Ӧ���ȼ�0
	NVICInit.NVIC_IRQChannelCmd = ENABLE;	         //ʹ���ж�
	NVIC_Init(&NVICInit);                            //д������ 							 //д������
}
/*---------------------------------------
 ��������: PA0�ⲿ�жϷ������
 ����ʵ��: ͨ�������������������һ������
           �ļ�ʱ,��һ�������ش򿪶�ʱ��
		   �ڶ��������عرն�ʱ��,������
		   ʱ������,��ն�ʱ�����һ�β��� 
---------------------------------------*/
void EXTI0_IRQHandler(void)
{
	OSIntNesting++;
	InterruptTimes++;
	
	if(InterruptTimes == 1)			//��1�ν����жϺ�򿪶�ʱ��5�ұ���½��ش���
	{	
		TIM_Cmd(TIM5,ENABLE);
		EXTI_IO_Init.EXTI_Line = EXTI_Line0; 
		EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		
		EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Falling;    
		EXTI_IO_Init.EXTI_LineCmd = ENABLE;				  
		EXTI_Init(&EXTI_IO_Init);
	}

	if(InterruptTimes == 2)			//��2�ν����жϺ��ȡ5CNT�ұ�������ش���
	{ 	
		WaveInfo.LowWidth = TIM5->CNT;
		EXTI_IO_Init.EXTI_Line = EXTI_Line0; 
		EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		
		EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Rising;   
		EXTI_IO_Init.EXTI_LineCmd = ENABLE;				   
		EXTI_Init(&EXTI_IO_Init);
	}
						 
	if(InterruptTimes == 3)			//��3�ν����жϺ�رն�ʱ��5�ҹر��ⲿ�ж�0
	{
	 	TIM_Cmd(TIM5,DISABLE);
		EXTI->IMR &= ~EXTI_Line0; 	
	}
	 
	EXTI_ClearFlag(EXTI_Line0);		
	OSIntExit();
}
/*---------------------------------------
 ��������: PA1�ⲿ�жϷ������
 ����ʵ��: ͨ��һ�������ػ�һ���½������
           һ��һϵ�е�ADת���Ĵ��������
		   �����ô���װ��,��ɼ����Ĳ���
		   ��ζ����������޷��۲�,���ñ���
		   ����֮������ȶ��۲Ⲩ�Ρ� 
---------------------------------------*/
void EXTI1_IRQHandler(void)
{
	OSIntNesting++;		
	if(WaveCtrl.TriggerMode == Trigger_Rising)	   //�����ش���AD
	{
	 	TIM_Cmd(TIM3,ENABLE);
		EXTI->RTSR |= EXTI_Line1;	   
    	EXTI->FTSR &= ~EXTI_Line1;
	}

	if(WaveCtrl.TriggerMode == Trigger_Falling)	   //�½��ش���AD
	{
	 	TIM_Cmd(TIM3,ENABLE);
		EXTI->RTSR &= ~EXTI_Line1;	   
    	EXTI->FTSR |=  EXTI_Line1;	
	}

	EXTI->IMR &= ~EXTI_Line1;					   //���1��AD������ر��ⲿ�ж�1,�´κ�ʱ�������������
	EXTI_ClearFlag(EXTI_Line1);		
	OSIntExit();
}
					   
