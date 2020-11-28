#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   	 
#include "key.h"	  	 	 
#include "lcd.h" 
#include "24cxx.h"	 
#include "touch.h"			 
#include "malloc.h"			 	
#include "includes.h" 
//ALIENTEK MiniSTM32开发板实验37
//UCOSII实验3-消息队列、信号量集和软件定时器 
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
 			   
//LED任务
//设置任务优先级
#define LED_TASK_PRIO       			7 
//设置任务堆栈大小
#define LED_STK_SIZE  		    		64
//任务堆栈
OS_STK LED_TASK_STK[LED_STK_SIZE];
//任务函数
void led_task(void *pdata);

//触摸屏任务
//设置任务优先级
#define TOUCH_TASK_PRIO       		 	6
//设置任务堆栈大小
#define TOUCH_STK_SIZE  				128
//任务堆栈	
OS_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//任务函数
void touch_task(void *pdata);

//队列消息显示任务
//设置任务优先级
#define QMSGSHOW_TASK_PRIO    			5 
//设置任务堆栈大小
#define QMSGSHOW_STK_SIZE  		 		64
//任务堆栈	
OS_STK QMSGSHOW_TASK_STK[QMSGSHOW_STK_SIZE];
//任务函数
void qmsgshow_task(void *pdata);


//主任务
//设置任务优先级
#define MAIN_TASK_PRIO       			4 
//设置任务堆栈大小
#define MAIN_STK_SIZE  					128
//任务堆栈	
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];
//任务函数
void main_task(void *pdata);

//信号量集任务
//设置任务优先级
#define FLAGS_TASK_PRIO       			3 
//设置任务堆栈大小
#define FLAGS_STK_SIZE  		 		64
//任务堆栈	
OS_STK FLAGS_TASK_STK[FLAGS_STK_SIZE];
//任务函数
void flags_task(void *pdata);


//按键扫描任务
//设置任务优先级
#define KEY_TASK_PRIO       			2 
//设置任务堆栈大小
#define KEY_STK_SIZE  					64
//任务堆栈	
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//任务函数
void key_task(void *pdata);
//////////////////////////////////////////////////////////////////////////////
    
OS_EVENT * msg_key;			//按键邮箱事件块	  
OS_EVENT * q_msg;			//消息队列
OS_TMR   * tmr1;			//软件定时器1
OS_TMR   * tmr2;			//软件定时器2
OS_TMR   * tmr3;			//软件定时器3
OS_FLAG_GRP * flags_key;	//按键信号量集
void * MsgGrp[256];			//消息队列存储地址,最大支持256个消息

//软件定时器1的回调函数	
//每100ms执行一次,用于显示CPU使用率和内存使用率		   
void tmr1_callback(OS_TMR *ptmr,void *p_arg) 
{
 	static u16 cpuusage=0;
	static u8 tcnt=0;	    
	POINT_COLOR=BLUE;
	if(tcnt==5)
	{
 		LCD_ShowxNum(182,10,cpuusage/5,3,16,0);			//显示CPU使用率  
		cpuusage=0;
		tcnt=0; 
	}
	cpuusage+=OSCPUUsage;
	tcnt++;				    
 	LCD_ShowxNum(182,30,mem_perused(),3,16,0);	//显示内存使用率	 	  		 					    
	LCD_ShowxNum(182,50,((OS_Q*)(q_msg->OSEventPtr))->OSQEntries,3,16,0X80);//显示队列当前的大小		   
 }

//软件定时器2的回调函数				  	   
void tmr2_callback(OS_TMR *ptmr,void *p_arg) 
{	
	static u8 sta=0;
	switch(sta)
	{
		case 0:
			LCD_Fill(121,221,lcddev.width-1,lcddev.height-1,RED);
			break;
		case 1:
			LCD_Fill(121,221,lcddev.width-1,lcddev.height-1,GREEN);
			break;
		case 2:		    
			LCD_Fill(121,221,lcddev.width-1,lcddev.height-1,BLUE);
			break;
		case 3:
			LCD_Fill(121,221,lcddev.width-1,lcddev.height-1,MAGENTA);
			break;
 		case 4:
			LCD_Fill(121,221,lcddev.width-1,lcddev.height-1,GBLUE);
			break;
		case 5:
			LCD_Fill(121,221,lcddev.width-1,lcddev.height-1,YELLOW);
			break;
		case 6:
			LCD_Fill(121,221,lcddev.width-1,lcddev.height-1,BRRED);
			break;	 
	}
	sta++;
	if(sta>6)sta=0;	 											   
}
//软件定时器3的回调函数				  	   
void tmr3_callback(OS_TMR *ptmr,void *p_arg) 
{	
	u8* p;	 
	u8 err; 
	static u8 msg_cnt=0;	//msg编号	  
	p=mymalloc(13);	//申请13个字节的内存
	if(p)
	{
	 	sprintf((char*)p,"ALIENTEK %03d",msg_cnt);
		msg_cnt++;
		err=OSQPost(q_msg,p);	//发送队列
		if(err!=OS_ERR_NONE) 	//发送失败
		{
			myfree(p);	//释放内存
			OSTmrStop(tmr3,OS_TMR_OPT_NONE,0,&err);	//关闭软件定时器3
 		}
	}
} 
//加载主界面   
void ucos_load_main_ui(void)
{
	LCD_Clear(WHITE);	//清屏
 	POINT_COLOR=RED;	//设置字体为红色 
	LCD_ShowString(10,10,200,16,16,"Mini STM32");	
	LCD_ShowString(10,30,200,16,16,"UCOSII TEST3");	
	LCD_ShowString(10,50,200,16,16,"ATOM@ALIENTEK");
   	LCD_ShowString(10,75,240,16,16,"KEY_UP:ADJUST");	
   	LCD_ShowString(10,95,240,16,16,"KEY0:Q ON/OFF   KEY1:TMR2 SW");	
 	LCD_DrawLine(0,70,lcddev.width,70);
	LCD_DrawLine(120,0,120,70);

 	LCD_DrawLine(0,120,lcddev.width,120);
 	LCD_DrawLine(0,220,lcddev.width,220);
	LCD_DrawLine(120,120,120,lcddev.height);
		    
 	LCD_ShowString(5,125,240,16,16,"QUEUE MSG");//队列消息
	LCD_ShowString(5,150,240,16,16,"Message:");	 
	LCD_ShowString(5+120,125,240,16,16,"FLAGS");//信号量集
	LCD_ShowString(5,225,240,16,16,"TOUCH");	//触摸屏
	LCD_ShowString(5+120,225,240,16,16,"TMR2");	//队列消息
	POINT_COLOR=BLUE;//设置字体为蓝色 
  	LCD_ShowString(150,10,200,16,16,"CPU:   %");	
   	LCD_ShowString(150,30,200,16,16,"MEM:   %");	
   	LCD_ShowString(150,50,200,16,16," Q :000");	

	delay_ms(300);
}	 
											   
int main(void)
{		
 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 
	KEY_Init();				//按键初始化   
	mem_init();				//初始化内存池
   	tp_dev.init();
	ucos_load_main_ui(); 
	OSInit();  	 			//初始化UCOSII
  	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	    
}							    

//开始任务
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	u8 err;	    	    
	pdata = pdata; 	
	msg_key=OSMboxCreate((void*)0);		//创建消息邮箱
	q_msg=OSQCreate(&MsgGrp[0],256);	//创建消息队列
 	flags_key=OSFlagCreate(0,&err); 	//创建信号量集		  
	  
	OSStatInit();					//初始化统计任务.这里会延时1秒钟左右	
 	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);						   
 	OSTaskCreate(touch_task,(void *)0,(OS_STK*)&TOUCH_TASK_STK[TOUCH_STK_SIZE-1],TOUCH_TASK_PRIO);	 				   
 	OSTaskCreate(qmsgshow_task,(void *)0,(OS_STK*)&QMSGSHOW_TASK_STK[QMSGSHOW_STK_SIZE-1],QMSGSHOW_TASK_PRIO);	 				   
 	OSTaskCreate(main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_STK_SIZE-1],MAIN_TASK_PRIO);	 				   
 	OSTaskCreate(flags_task,(void *)0,(OS_STK*)&FLAGS_TASK_STK[FLAGS_STK_SIZE-1],FLAGS_TASK_PRIO);	 				   
 	OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	 				   
 	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}
//LED任务
void led_task(void *pdata)
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
//触摸屏任务
void touch_task(void *pdata)
{	  	
	while(1)
	{
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)		//触摸屏被按下
		{	
		 	if(tp_dev.x[0]<120&&tp_dev.y[0]<lcddev.height&&tp_dev.y[0]>220)
			{													   
				TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],BLUE);		//画图	 
				delay_ms(2); 			   
			}
		}else delay_ms(10);	//没有按键按下的时候 
	}
}     
//队列消息显示任务
void qmsgshow_task(void *pdata)
{
	u8 *p;
	u8 err;
	while(1)
	{
		p=OSQPend(q_msg,0,&err);//请求消息队列
		LCD_ShowString(5,170,240,16,16,p);//显示消息
 		myfree(p);	  
		delay_ms(500);	 
	}									 
}
//主任务
void main_task(void *pdata)
{							 
	u32 key=0;	
	u8 err;	
 	u8 tmr2sta=1;	//软件定时器2开关状态   
 	u8 tmr3sta=0;	//软件定时器3开关状态
	u8 flagsclrt=0;	//信号量集显示清零倒计时   
 	tmr1=OSTmrCreate(10,10,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,0,"tmr1",&err);		//100ms执行一次
	tmr2=OSTmrCreate(10,20,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr2_callback,0,"tmr2",&err);		//200ms执行一次
	tmr3=OSTmrCreate(10,10,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr3_callback,0,"tmr3",&err);		//100ms执行一次
	OSTmrStart(tmr1,&err);//启动软件定时器1				 
	OSTmrStart(tmr2,&err);//启动软件定时器2				 
 	while(1)
	{
		key=(u32)OSMboxPend(msg_key,10,&err); 
		if(key)
		{
			flagsclrt=51;//500ms后清除
			OSFlagPost(flags_key,1<<(key-1),OS_FLAG_SET,&err);//设置对应的信号量为1
		}
		if(flagsclrt)//倒计时
		{
			flagsclrt--;
			if(flagsclrt==1)LCD_Fill(140,162,239,162+16,WHITE);//清除显示
		}
		switch(key)
		{ 
			case KEY0_PRES://软件定时器3开关	 
				tmr3sta=!tmr3sta;
				if(tmr3sta)OSTmrStart(tmr3,&err);  
				else OSTmrStop(tmr3,OS_TMR_OPT_NONE,0,&err);		//关闭软件定时器3
 				break; 
			case KEY1_PRES://软件定时器2开关&触摸区域清空
				tmr2sta=!tmr2sta;
				if(tmr2sta)OSTmrStart(tmr2,&err);			  	//开启软件定时器2
				else 
				{		    		    
  					OSTmrStop(tmr2,OS_TMR_OPT_NONE,0,&err);	//关闭软件定时器2
 					LCD_ShowString(148,262,240,16,16,"TMR2 STOP");//提示定时器2关闭了	
				}
				LCD_Fill(0,221,120-1,lcddev.height-1,WHITE);//触摸区域清空
				break;	
			case WKUP_PRES://校准
				OSTaskSuspend(TOUCH_TASK_PRIO);						//挂起触摸屏任务		 
				OSTaskSuspend(QMSGSHOW_TASK_PRIO);	 				//挂起队列信息显示任务		 
 				OSTmrStop(tmr1,OS_TMR_OPT_NONE,0,&err);				//关闭软件定时器1
				if(tmr2sta)OSTmrStop(tmr2,OS_TMR_OPT_NONE,0,&err);	//关闭软件定时器2				 
 				if((tp_dev.touchtype&0X80)==0)TP_Adjust();	 
				OSTmrStart(tmr1,&err);				//重新开启软件定时器1
				if(tmr2sta)OSTmrStart(tmr2,&err);	//重新开启软件定时器2	 
 				OSTaskResume(TOUCH_TASK_PRIO);		//解挂
 				OSTaskResume(QMSGSHOW_TASK_PRIO); 	//解挂
				ucos_load_main_ui();				//重新加载主界面		 
				break;			 
				
		}  
		delay_ms(10);
	}
}		   
//信号量集处理任务
void flags_task(void *pdata)
{	
	u16 flags;	
	u8 err;	    						 
	while(1)
	{
		flags=OSFlagPend(flags_key,0X001F,OS_FLAG_WAIT_SET_ANY,0,&err);//等待信号量
		if(flags&0X0001)LCD_ShowString(140,162,240,16,16,"KEY0 DOWN  "); 
		if(flags&0X0002)LCD_ShowString(140,162,240,16,16,"KEY1 DOWN  "); 
		if(flags&0X0004)LCD_ShowString(140,162,240,16,16,"KEY_UP DOWN"); 
		LED1=0;
		delay_ms(50);
		LED1=1;
		OSFlagPost(flags_key,0X0007,OS_FLAG_CLR,&err);//全部信号量清零
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









