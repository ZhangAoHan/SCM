/*-----------------------------------------------
		���������˿����ü�������
	˵��:	�Ѿ����˿����úͰ���ɨ������װ����
	        ���ݳ���ʵ����Ҫ������Ӧ�Ĳ������ɡ�
	ʱ��:	2013��7��22��
------------------------------------------------*/
#include "indkey.h"
#include "stm32f10x.h"
#include "delay.h"
#include "oscilloscope.h"
#include "ucos_ii.h"
/*-----------------------------------------
		    	��������
------------------------------------------*/
extern WaveType WaveInfo;
extern WaveMode WaveCtrl;
/*-----------------------------------------------
	��������:	�����������
	��������:	�˿�����GPIOx,������GPIO_Pin
	������ֵ:	INT8U���� ����ֵ0,1
------------------------------------------------*/
unsigned char Key_Scan(GPIO_TypeDef* GPIOx,unsigned short int GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_PRESSED)  //���½�ͨ�͵�ƽ
	{
		delayms(3);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_PRESSED)
		{
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_PRESSED);//�ȴ������ͷ�
			return KEY_PRESSED;
		}
		else
			return KEY_UNPRESS;
	}
	else
		return KEY_UNPRESS;
}
/*---------------------------------------------------------------
	��������: �ⲿ�ж�����ģ��,����B10,B11��Ϊ�ⲿ�½����ж� 
----------------------------------------------------------------*/
void Key_EXTI_Config(void)
{
	NVIC_InitTypeDef NVICInit;
	EXTI_InitTypeDef EXTI_IO_Init;

	NVICInit.NVIC_IRQChannel = EXTI15_10_IRQn;			 //0-4����IV,5-9����EXTI9_5_IRQn IV,10-15����EXTI15_10_IRQn IV	
	NVICInit.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2
    NVICInit.NVIC_IRQChannelSubPriority = 1;  		 //��Ӧ���ȼ�1
	NVICInit.NVIC_IRQChannelCmd = ENABLE;	         //ʹ���ж�
	NVIC_Init(&NVICInit);                            //д������ 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);
	EXTI_IO_Init.EXTI_Line = EXTI_Line10; 
	EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		//�ж�ģʽ
	EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Falling;   //�½��ش����ж�
	EXTI_IO_Init.EXTI_LineCmd = ENABLE;				    //ʹ���ж�
	EXTI_Init(&EXTI_IO_Init);	 					    //д������

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);
	EXTI_IO_Init.EXTI_Line = EXTI_Line11; 
	EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		//�ж�ģʽ
	EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Falling;   //�½��ش����ж�
	EXTI_IO_Init.EXTI_LineCmd = ENABLE;				    //ʹ���ж�
	EXTI_Init(&EXTI_IO_Init);	 					    //д������
}
/*---------------------------------------------------------------
	��������: ���������ж� 
----------------------------------------------------------------*/
void EXTI15_10_IRQHandler(void)
{
	OSIntNesting++;
	if(EXTI_GetITStatus(EXTI_Line10) == SET)
	{	   
	   ManualGainScan(++WaveCtrl.Gain);
	   if(WaveCtrl.Gain == 9)
	   	WaveCtrl.Gain = 1;
	   EXTI_ClearFlag(EXTI_Line10);
	}	
	
	if(EXTI_GetITStatus(EXTI_Line11) == SET)
	{	   
	   ManualGainScan(--WaveCtrl.Gain);
	   if(WaveCtrl.Gain == 0)
	   	WaveCtrl.Gain = 8;
	   EXTI_ClearFlag(EXTI_Line11);
	}		
	OSIntExit();
}
