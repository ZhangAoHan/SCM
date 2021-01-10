/*------------------------------------------------------------------------------------
        		   					STM32ʾ����
 Ӳ��ƽ̨:
 			������: STM32F103ZET6 64K RAM 512K ROM
			��Ļ��: SSD1963 
			�ֱ���: 480x272 16λɫ
           	������: TSC2046
			ģ���·: OP  - TL084
					  OP  - u741
					  SW  - CD4051
					  CMP - LM311
					  PWR - LM7805
					      - LM7905
						  - MC34063
						  - AMS1117-3.3
					  DRI - ULN2003
			�̵������źż̵���
		    ��Դ:   DC +12V

 ���ƽ̨:
 			��������: RealView MDK-ARM uVision4.10
			C������ : ARMCC
			ASM������:ARMASM
			������:   ARMLINK
			ʵʱ�ں�: uC/OS-II 2.90ʵʱ����ϵͳ
			GUI�ں� : uC/GUI   3.90ͼ���û��ӿ�
			�ײ�����: ����������������
	
	ROM Size = Code + RO-data +RW-data
	RAM Size = RW-data + ZI-data
	Program Size: Code=56024 RO-data=8272 RW-data=256 ZI-data=29912          
 
 ʱ��: 2013��11��9��       BoX��д�ڴ����ѧ��
 
 �汾: V1.0 - 2013/11/9
       V1.1 - 2014/2/8
	   V3.0 - 2014/2/19				
-------------------------------------------------------------------------------------*/   
#include "stm32f10x.h"
#include "ucos_ii.h"
#include "app.h"
#include "GUI.h"

#include "usart1.h"
#include "pincfg.h"
#include "delay.h"
#include "tft_api.h"
#include "dac.h"
#include "adc.h"
#include "iwdg.h"
#include "timer.h"
#include "EXTI.H"
#include "oscilloscope.h"
#include "indkey.h"
#include "tsc2046.h"

#include "task_rtc.h"
#include "task_gui.h"
#include "task_sd.h"


/*-----------------------------------------
				������ʼ����ջ
------------------------------------------*/
OS_STK  Task_Start_Stk[TASK_START_STK_SIZE]; 

/*-----------------------------------------
 ��Ϊ�漰���Թ�����Դ�ķ���,���������ź���
------------------------------------------*/
OS_EVENT *LCD_Buffer_MUTEX;
OS_EVENT *USART_Buffer_MUTEX;
OS_EVENT *SDtoRAM_Buffer_MUTEX;
/*-----------------------------------------
				�� �� ��
------------------------------------------*/    
int main(void)    
{    
	 INT8U err;
     SystemInit();		 //��ʼ��RCCʱ��
	 OSInit(); 
	  		 
	 LCD_Buffer_MUTEX     = OSMutexCreate(4,&err);	//����3��������Դ�����ź���
	 USART_Buffer_MUTEX   = OSMutexCreate(4,&err);
	 SDtoRAM_Buffer_MUTEX = OSMutexCreate(4,&err);
	    
     OSTaskCreate(Task_Start,(void *)0,&Task_Start_Stk[TASK_START_STK_SIZE-1],TASK_START_PRIO); //��ʼ����   
	 
	 OSStart();       
}
/*-------------------------------------------------------------------------------
 ��������:��ʼ����������
 ˵    ��:��Ϊ�ܲ���ϵͳ,��������ĳ�ʼ��Ӧ�÷��ڲ���ϵͳ�ĳ�ʼ���������,����
          ��while(1)ѭ���ⲿ�������ĳ�ʼ������,�������ϵͳ�����޷�����.
		  ��������app.c�б�����
-------------------------------------------------------------------------------*/
void BSP_Init(void)
{
	OS_CPU_SR  cpu_sr = 0u;
	OS_ENTER_CRITICAL();
	DelayInit();		 //��ʼ����ʱ
	PinCfg();			 //�ⲿ������������
	FSMC_LCD_Init();	 //FSMC��������		  
	GUI_Init();			 //��ʼ��UCGUI����
	TSC2046_Config();	 //��ʼ������������
	USART1_Config();	 //��ʼ������
	DAC_Config();		 //��ʼ��DAC1
	ADC1_Init();		 //��ʼ��ADC1
	EXTI_Config();		 //��ʼ���ⲿ�ж�
	Key_EXTI_Config();	 //��ʼ�������ж�
	TIM5_Config(1999,71);  //TIM5��1MHzƵ�ʼ���,ÿ2ms����ж�
//	TIM4_Config(59999,71); //TIM4��1MHzƵ�ʼ���,ÿ60ms����ж�
	RTC_Init();	 	 	  //��ʼ��RTC
//	SD_Init();
	JDQ_ACDC = 1;		  //�������
	ManualGainScan(3);    //������
	IWDG_Init(4,625);     //ι��ʱ��Ϊ1000ms
	OS_EXIT_CRITICAL();	 
}
