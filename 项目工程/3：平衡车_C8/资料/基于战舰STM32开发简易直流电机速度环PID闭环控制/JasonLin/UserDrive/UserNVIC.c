#include"stm32f10x.h"


void UserNVIC_Configuration(void)
{
   NVIC_InitTypeDef NVIC_InitStructure; 

   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		   //�жϷ���2 ��λ��ռ��0-3��  ��λ��Ӧ��0-3��

   NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 		  
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
   NVIC_Init(&NVIC_InitStructure);

   //*****************************************************

   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 		 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   //******************************************************
 
   NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 		 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
   NVIC_Init(&NVIC_InitStructure);

   //*******************************************************
 
   NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; 		 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   //*******************************************************

   NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 	
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

 
 /*���ȼ����飺���ȼ�������Ϊ�˸���ռʽ���ȼ�����Ӧ���ȼ����ж����ȼ��Ĵ����ĸ���λ���������ռ��λ��
               ��ͬһ�����������ȼ�����ֻ���趨һ�� */

 /*��ռ���ȼ�: ��һ���ж�����ִ�ж���һ�����и�����ռ���ȼ����жϵ���ʱ����ռ���ȼ��ߵľͻ���ռCPU����Ȩ
 			   ��ʱ�����жϾ�����Ƕ���жϹ�ϵ��������ͬ��ռ���ȼ����ж�û��Ƕ�׹�ϵ*/

 /*��Ӧ���ȼ����������ȼ�����������ռ���ȼ���ͬ���ж�ͬʱ������������Ӧ���ȼ��ߵ��ж����Ȼ��CPU�Ĵ���Ȩ
               ����жϲ���ͬʱ�������������Ҫ�ȴ�����ִ�е��жϴ�������ܻ����Ӧ*/

}

