/*------------------------------------------------------------------------------------
        		   		STM32+UCOS+UCGUIʾ����
 ˵��: дAPP����app.c���,��ģ�����Ѿ����UCOS-II��STM32�ϵ���ֲ,���Ը�����Ŀ�Ĳ�ͬ�ü��ں�
	   ��С�����,����os_cfg.h��ɲü�.�������Դ�3��LED��ʾ1�����ڷ��͵Ķ�����ִ��.
	   
	   ����һ������Ĳ���:								
	   *(1) ��app.h�����������ȼ���ջ��С,Ҳ���Ǻ궨�塣
	   *(2) ��main�ļ��ж�������ջ OS_STK task_led1_stk[TASK_LED1_STK_SIZE]��
	   *(3) ��app.c�ж�������ľ�������Ҫ��ʲô,��ס��Ҫ��app.h�������������궨��ջ��С���궨�����ȼ�
	   *(4) ��main�����д������� 
	        OSTaskCreate(Task_LED1,(void *)0,&task_led1_stk[TASK_LED1_STK_SIZE-1], TASK_LED1_PRIO);
	   *(5) �������м������һ������Ĵ�����

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
#ifndef _APP_H_    
#define _APP_H_    
   
/*******************�����������ȼ�*******************/ 
#define TASK_START_PRIO				   5  
#define TASK_MAIN_PRIO                 11
#define TASK_RTC_PRIO                  12
#define TASK_SD_PRIO                   13
#define TASK_TOUCHSCREEN_PRIO          14
#define TASK_GUI_PRIO                  15           
 
/************����ջ��С����λΪ OS_STK ��************/   
#define TASK_GUI_STK_SIZE              1024
#define TASK_MAIN_STK_SIZE	           2048
#define TASK_RTC_STK_SIZE	           512
#define TASK_SD_STK_SIZE               512
#define TASK_TOUCHSCREEN_STK_SIZE      256
#define TASK_START_STK_SIZE				64 

/**************** �û��������� **********************/   
void Task_TouchScreen(void *pdata);
void Task_Main(void *pdata); 
void Task_RTC(void *pdata);
void Task_SD(void *pdata); 
void Task_GUI(void *pdata);
void Task_Start(void *pdata);

  
    
#endif  //_APP_H_
