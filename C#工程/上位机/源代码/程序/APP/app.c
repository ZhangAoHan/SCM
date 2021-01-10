/*------------------------------------------------------------------------------------
        		   	  STM32+UCOS+UCGUIʾ����
	   
	   					    �����б�
	   +---------------------+-------------+-----------+
	   |      ��������       | �������ȼ�  |  �����ջ |
	   +---------------------+-------------+-----------+	   
	   |   TASK_MAIN         |     11      |   2048    |
	   +---------------------+-------------+-----------+
	   |   TASK_RTC   	     |     12      |    512    |
	   +---------------------+-------------+-----------+
	   |   TASK_SD	         |     13      |    512    |
	   +---------------------+-------------+-----------+
	   |   TASK_TOUCHSCREEN	 |     14      |    512    |
	   +---------------------+-------------+-----------+
	   |   TASK_GUI	 		 |     15      |   1024    |
	   +---------------------+-------------+-----------+
	   |   TASK_START	     |     5       |    64     |
	   +---------------------+-------------+-----------+
	   

 ʱ��: 2013��11��13��       BoX��д				
-------------------------------------------------------------------------------------*/  
#include "ucos_ii.h"   
#include "stdio.h"
#include "app.h"
#include "pincfg.h"
#include "delay.h"
#include "tft_api.h"
#include "oscilloscope.h"
#include "indkey.h"
#include "timer.h"
#include "EXTI.H"
#include "adc.h"
#include "iwdg.h"
#include "tsc2046.h"

#include "task_main.h"
#include "task_gui.h"
#include "task_rtc.h"
#include "task_sd.h"
#include "task_touchscreen.h"

#include "GUI.h"
/*-----------------------------------------
				��������ջ
 UCOSII�������ջû��8�ֽڶ���,�����������
 ջʱ,ǿ��8�ֽڶ���Ϳ�����,ϵͳĬ����4�ֽ�
 ����.����sprintfʱ�������,ϵͳ�����.
------------------------------------------*/
__align(8) OS_STK Task_TouchScreen_Stk[TASK_TOUCHSCREEN_STK_SIZE];
__align(8) OS_STK Task_Main_Stk[TASK_MAIN_STK_SIZE];
__align(8) OS_STK Task_RTC_Stk[TASK_RTC_STK_SIZE];
__align(8) OS_STK Task_SD_Stk [TASK_SD_STK_SIZE];
__align(8) OS_STK Task_GUI_Stk[TASK_GUI_STK_SIZE];
/*-----------------------------------------
		    	��������
------------------------------------------*/
extern u16  ADC1_DMA_Value;
extern u8   LCD_Buffer[LCD_BUFFER_SIZE];
extern u16  Tpx,Tpy,ZBX,ZBY;		  //������ADֵ,����ֵ
extern void BSP_Init(void);

extern  WaveType    WaveInfo;			  //���β���
extern  WaveMode    WaveCtrl;			  //���Ʋ���
extern  FG_WaveType FG_WaveInfo;	      //�źŷ���������
/*-----------------------------------------
		    	��ʼ����
------------------------------------------*/
void Task_Start(void *pdata)
{
 	 pdata = pdata;
	 BSP_Init();		//���Ƭ������ĳ�ʼ��
	 OSStatInit();		//��ʼ��ͳ������
	 
	 while(1)
	 {	 
//	 	 ShowWelcomeScreen();
//		 OSTimeDlyHMSM(0,0,3,0);
	 	 /*����������*/
		 
	  	 OSTaskCreateExt(Task_TouchScreen,
                    	(void *)0,
                    	&Task_TouchScreen_Stk[TASK_TOUCHSCREEN_STK_SIZE - 1],
                    	TASK_TOUCHSCREEN_PRIO,
                    	TASK_TOUCHSCREEN_PRIO,
                    	&Task_TouchScreen_Stk[0],
                    	TASK_TOUCHSCREEN_STK_SIZE,
                    	(void *)0,
                    	OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
		
        /*ʵʱʱ������*/
        OSTaskCreateExt(Task_RTC,
	                    (void *)0,
	                    &Task_RTC_Stk[TASK_RTC_STK_SIZE - 1],
	                    TASK_RTC_PRIO,
	                    TASK_RTC_PRIO,
	                    &Task_RTC_Stk[0],
	                    TASK_RTC_STK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
        /*SD������*/
        OSTaskCreateExt(Task_SD,
	                    (void *)0,
	                    &Task_SD_Stk[TASK_SD_STK_SIZE - 1],
	                    TASK_SD_PRIO,
	                    TASK_SD_PRIO,
	                    &Task_SD_Stk[0],
	                    TASK_SD_STK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
		/*GUI����*/
		OSTaskCreateExt(Task_GUI,
                    	(void *)0,
	                    &Task_GUI_Stk[TASK_GUI_STK_SIZE - 1],
	                    TASK_GUI_PRIO,
	                    TASK_GUI_PRIO,
	                    &Task_GUI_Stk[0],
	                    TASK_GUI_STK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

		/*������*/
		OSTaskCreateExt(Task_Main,
	                    (void *)0,
	                    &Task_Main_Stk[TASK_MAIN_STK_SIZE - 1],
	                    TASK_MAIN_PRIO,
	                    TASK_MAIN_PRIO,
	                    &Task_Main_Stk[0],
	                    TASK_MAIN_STK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
  	    
//		PinCfg_Beep(1); 			   //������������ʾϵͳ�����ɹ�
        OSTaskSuspend(OS_PRIO_SELF);   //����Task_Start����		
	 }
}
/*-----------------------------------------
		    	����������
------------------------------------------*/	 
void Task_TouchScreen(void *pdata)
{
	pdata = pdata;
	while(1)
	{	
		TP_Read(&Tpx,&Tpy);
		TP_ADtoZB(&Tpx,&Tpy,&ZBX,&ZBY);	 //���㴥������
		TouchEventDetected();			 //��ⴥ���¼�
		BOARD_LED1 = !BOARD_LED1;
		OSTimeDlyHMSM(0,0,0,100);
	}
}
/*-----------------------------------------
		    	Real Time Clock����
------------------------------------------*/
void Task_RTC(void *pdata)
{
	pdata = pdata;	
	while(1)
	{	
		u8 AlarmTemp;
		GetFrequence();		   //��ȡʱ���������ʾ
		AlarmTemp = GetTempSensor();	
		
		if(AlarmTemp>60)	   //оƬ�����¶ȱ�����ֵ60��
			BEEP = 1;
		else if(AlarmTemp>50)
			PinCfg_Beep(3);	   //�ӽ����߶���3��
		else
			BEEP = 0;
	 	OSTimeDlyHMSM(0,0,1,500);
	} 	
}
/*-----------------------------------------
		     	������ 
------------------------------------------*/
void Task_Main(void *pdata)
{	
	pdata = pdata;					
	WaveCtrl.TimeBase = 99;			//�ϵ�Ĭ��ʱ��99
	WaveCtrl.Gain = 3;				//�ϵ�Ĭ�������3
	while(1)
	{
//		TaskStackChack();			//�Ƿ��ջʹ��������
		GetWaveADCValue();			//���ĺ���
		IWDG_Feed();       			//1000ms��ι��
		BOARD_LED2 = !BOARD_LED2;
		OSTimeDlyHMSM(0,0,0,50);
	}	
}
/*-----------------------------------------
		    	SD���� 
------------------------------------------*/
void Task_SD(void *pdata)
{
	pdata = pdata;
	while(1)
	{
		SendDataToPC();				//���ͱ������ݵ���λ��
	 	OSTimeDlyHMSM(0,0,0,999);
	}
}
/*-----------------------------------------
		    	GUI���� 
------------------------------------------*/ 

void Task_GUI(void *pdata)
{
	pdata = pdata;
	DrawControlPanel();
	while(1)
	{	
		DisplayWaveInfo();		  	//��ʾ����	
		OSTimeDlyHMSM(0,0,0,500);
	}
}
