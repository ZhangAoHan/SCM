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

//ALIENTEK MiniSTM32开发板实验36
//UCOSII实验2-信号量和邮箱 
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  

 
/////////////////////////UCOSII任务设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务堆栈	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);	
 			   
//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO       			7 
//设置任务堆栈大小
#define LED0_STK_SIZE  		    		64
//任务堆栈	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *pdata);

//触摸屏任务
//设置任务优先级
#define TOUCH_TASK_PRIO       		 	6
//设置任务堆栈大小
#define TOUCH_STK_SIZE  				128
//任务堆栈	
OS_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//任务函数
void touch_task(void *pdata);

//LED1任务
//设置任务优先级
#define LED1_TASK_PRIO       			5 
//设置任务堆栈大小
#define LED1_STK_SIZE  					64
//任务堆栈	
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数
void led1_task(void *pdata);


//主任务
//设置任务优先级
#define MAIN_TASK_PRIO       			4 
//设置任务堆栈大小
#define MAIN_STK_SIZE  					128
//任务堆栈	
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];
//任务函数
void main_task(void *pdata);

//按键扫描任务
//设置任务优先级
#define KEY_TASK_PRIO       			3 
//设置任务堆栈大小
#define KEY_STK_SIZE  					64
//任务堆栈	
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//任务函数
void key_task(void *pdata);
//////////////////////////////////////////////////////////////////////////////
OS_EVENT * msg_key;			//按键邮箱事件块指针
OS_EVENT * sem_led1;		//LED1信号量指针	 	  
//加载主界面   
void ucos_load_main_ui(void)
{
	LCD_Clear(WHITE);	//清屏
 	POINT_COLOR=RED;	//设置字体为红色 
	LCD_ShowString(30,10,200,16,16,"Mini STM32");	
	LCD_ShowString(30,30,200,16,16,"UCOSII TEST2");	
	LCD_ShowString(30,50,200,16,16,"ATOM@ALIENTEK");
   	LCD_ShowString(30,75,200,16,16,"KEY0:LED1 KEY_UP:ADJUST");	
   	LCD_ShowString(30,95,200,16,16,"KEY1:CLEAR"); 
	LCD_ShowString(80,210,200,16,16,"Touch Area");	
	LCD_DrawLine(0,120,lcddev.width,120);
	LCD_DrawLine(0,70,lcddev.width,70);
	LCD_DrawLine(150,0,150,70);
 	POINT_COLOR=BLUE;//设置字体为蓝色 
  	LCD_ShowString(160,30,200,16,16,"CPU:   %");	
   	LCD_ShowString(160,50,200,16,16,"SEM:000");	
}	  										   
int main(void)
{	 
 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD
	KEY_Init();				//按键初始化
   	tp_dev.init();		    //触摸屏初始化
	ucos_load_main_ui();	//加载主界面	 
  	OSInit();  	 			//初始化UCOSII
  	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	    
}

//开始任务
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 		  
	msg_key=OSMboxCreate((void*)0);	//创建消息邮箱
	sem_led1=OSSemCreate(0);		//创建信号量		 			  
	OSStatInit();					//初始化统计任务.这里会延时1秒钟左右	
 	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);						   
 	OSTaskCreate(touch_task,(void *)0,(OS_STK*)&TOUCH_TASK_STK[TOUCH_STK_SIZE-1],TOUCH_TASK_PRIO);	 				   
 	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);	 				   
 	OSTaskCreate(main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_STK_SIZE-1],MAIN_TASK_PRIO);	 				   
 	OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	 				   
 	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}	  
//LED0任务
void led0_task(void *pdata)
{
	u8 t;
	while(1)
	{
		t++;
		delay_ms(10);
		if(t==8)LED0=1;	//LED0灭
		if(t==100)		//LED0亮
		{
			t=0;
			LED0=0;
		}
	}									 
}	   

//LED1任务
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
//触摸屏任务
void touch_task(void *pdata)
{	  	
	while(1)
	{
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)		//触摸屏被按下
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height&&tp_dev.y[0]>120)
			{													   
				TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//画图	 
				delay_ms(2); 			   
			}
		}else delay_ms(10);	//没有按键按下的时候 
	}
}
//主任务
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
			case KEY0_PRES://发送信号量
				semmask=1;
				OSSemPost(sem_led1);
				break;
			case KEY1_PRES://清除
				LCD_Fill(0,121,lcddev.width,lcddev.height,WHITE);
				break;
			case WKUP_PRES://校准
				OSTaskSuspend(TOUCH_TASK_PRIO);	//挂起触摸屏任务		 
 				if((tp_dev.touchtype&0X80)==0)TP_Adjust();	   
 				OSTaskResume(TOUCH_TASK_PRIO);	//解挂
				ucos_load_main_ui();			//重新加载主界面		 
				break;
		}
   		if(semmask||sem_led1->OSEventCnt)//需要显示sem		
		{
			POINT_COLOR=BLUE;
			LCD_ShowxNum(192,50,sem_led1->OSEventCnt,3,16,0X80);//显示信号量的值
			if(sem_led1->OSEventCnt==0)semmask=0;	//停止更新
		} 
		if(tcnt==50)//0.5秒更新一次CPU使用率
		{
			tcnt=0;
			POINT_COLOR=BLUE;		  
			LCD_ShowxNum(192,30,OSCPUUsage,3,16,0);	//显示CPU使用率   
		}
		tcnt++;
		delay_ms(10);
	}
}

//按键扫描任务
void key_task(void *pdata)
{	
	u8 key;		    						 
	while(1)
	{
		key=KEY_Scan(0);   
		if(key)OSMboxPost(msg_key,(void*)key);//发送消息
 		delay_ms(10);
	}
}

























