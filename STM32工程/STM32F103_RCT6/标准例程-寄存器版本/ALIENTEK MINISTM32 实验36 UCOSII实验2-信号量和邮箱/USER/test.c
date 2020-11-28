#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   	 
#include "key.h"	 	 
#include "exti.h"	 	 
#include "wdg.h" 	 
#include "timer.h"	 	 	 
#include "lcd.h"
#include "usmart.h"	
#include "rtc.h"
#include "wkup.h"	
#include "adc.h"	
#include "dac.h"	
#include "dma.h"	
#include "24cxx.h"	
#include "flash.h"	
#include "touch.h"			 	
#include "includes.h"

//ALIENTEK MiniSTM32������ʵ��36
//UCOSIIʵ��2-�ź��������� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

 
/////////////////////////UCOSII��������///////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO      			10 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//�����ջ	
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);	
 			   
//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO       			7 
//���������ջ��С
#define LED0_STK_SIZE  		    		64
//�����ջ	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *pdata);

//����������
//�����������ȼ�
#define TOUCH_TASK_PRIO       		 	6
//���������ջ��С
#define TOUCH_STK_SIZE  				128
//�����ջ	
OS_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//������
void touch_task(void *pdata);

//LED1����
//�����������ȼ�
#define LED1_TASK_PRIO       			5 
//���������ջ��С
#define LED1_STK_SIZE  					64
//�����ջ	
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *pdata);


//������
//�����������ȼ�
#define MAIN_TASK_PRIO       			4 
//���������ջ��С
#define MAIN_STK_SIZE  					128
//�����ջ	
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];
//������
void main_task(void *pdata);

//����ɨ������
//�����������ȼ�
#define KEY_TASK_PRIO       			3 
//���������ջ��С
#define KEY_STK_SIZE  					64
//�����ջ	
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//������
void key_task(void *pdata);
//////////////////////////////////////////////////////////////////////////////
OS_EVENT * msg_key;			//���������¼���ָ��
OS_EVENT * sem_led1;		//LED1�ź���ָ��	 	  
//����������   
void ucos_load_main_ui(void)
{
	LCD_Clear(WHITE);	//����
 	POINT_COLOR=RED;	//��������Ϊ��ɫ 
	LCD_ShowString(30,10,200,16,16,"Mini STM32");	
	LCD_ShowString(30,30,200,16,16,"UCOSII TEST2");	
	LCD_ShowString(30,50,200,16,16,"ATOM@ALIENTEK");
   	LCD_ShowString(30,75,200,16,16,"KEY0:LED1 KEY_UP:ADJUST");	
   	LCD_ShowString(30,95,200,16,16,"KEY1:CLEAR"); 
	LCD_ShowString(80,210,200,16,16,"Touch Area");	
	LCD_DrawLine(0,120,lcddev.width,120);
	LCD_DrawLine(0,70,lcddev.width,70);
	LCD_DrawLine(150,0,150,70);
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
  	LCD_ShowString(160,30,200,16,16,"CPU:   %");	
   	LCD_ShowString(160,50,200,16,16,"SEM:000");	
}	  										   
int main(void)
{	 
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD
	KEY_Init();				//������ʼ��
   	tp_dev.init();		    //��������ʼ��
	ucos_load_main_ui();	//����������	 
  	OSInit();  	 			//��ʼ��UCOSII
  	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
	OSStart();	    
}

//��ʼ����
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 		  
	msg_key=OSMboxCreate((void*)0);	//������Ϣ����
	sem_led1=OSSemCreate(0);		//�����ź���		 			  
	OSStatInit();					//��ʼ��ͳ������.�������ʱ1��������	
 	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);						   
 	OSTaskCreate(touch_task,(void *)0,(OS_STK*)&TOUCH_TASK_STK[TOUCH_STK_SIZE-1],TOUCH_TASK_PRIO);	 				   
 	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);	 				   
 	OSTaskCreate(main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_STK_SIZE-1],MAIN_TASK_PRIO);	 				   
 	OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	 				   
 	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}	  
//LED0����
void led0_task(void *pdata)
{
	u8 t;
	while(1)
	{
		t++;
		delay_ms(10);
		if(t==8)LED0=1;	//LED0��
		if(t==100)		//LED0��
		{
			t=0;
			LED0=0;
		}
	}									 
}	   

//LED1����
void led1_task(void *pdata)
{
	u8 err;
	while(1)
	{
		OSSemPend(sem_led1,0,&err);
		LED1=0;
		delay_ms(200);
		LED1=1;
		delay_ms(800);
	}									 
}
//����������
void touch_task(void *pdata)
{	  	
	while(1)
	{
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)		//������������
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height&&tp_dev.y[0]>120)
			{													   
				TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//��ͼ	 
				delay_ms(2); 			   
			}
		}else delay_ms(10);	//û�а������µ�ʱ�� 
	}
}
//������
void main_task(void *pdata)
{							 
	u32 key=0;	
	u8 err;	
	u8 semmask=0;
	u8 tcnt=0;						 
	while(1)
	{
		key=(u32)OSMboxPend(msg_key,10,&err);   
		switch(key)
		{ 
			case KEY0_PRES://�����ź���
				semmask=1;
				OSSemPost(sem_led1);
				break;
			case KEY1_PRES://���
				LCD_Fill(0,121,lcddev.width,lcddev.height,WHITE);
				break;
			case WKUP_PRES://У׼
				OSTaskSuspend(TOUCH_TASK_PRIO);	//������������		 
 				if((tp_dev.touchtype&0X80)==0)TP_Adjust();	   
 				OSTaskResume(TOUCH_TASK_PRIO);	//���
				ucos_load_main_ui();			//���¼���������		 
				break;
		}
   		if(semmask||sem_led1->OSEventCnt)//��Ҫ��ʾsem		
		{
			POINT_COLOR=BLUE;
			LCD_ShowxNum(192,50,sem_led1->OSEventCnt,3,16,0X80);//��ʾ�ź�����ֵ
			if(sem_led1->OSEventCnt==0)semmask=0;	//ֹͣ����
		} 
		if(tcnt==50)//0.5�����һ��CPUʹ����
		{
			tcnt=0;
			POINT_COLOR=BLUE;		  
			LCD_ShowxNum(192,30,OSCPUUsage,3,16,0);	//��ʾCPUʹ����   
		}
		tcnt++;
		delay_ms(10);
	}
}

//����ɨ������
void key_task(void *pdata)
{	
	u8 key;		    						 
	while(1)
	{
		key=KEY_Scan(0);   
		if(key)OSMboxPost(msg_key,(void*)key);//������Ϣ
 		delay_ms(10);
	}
}

























