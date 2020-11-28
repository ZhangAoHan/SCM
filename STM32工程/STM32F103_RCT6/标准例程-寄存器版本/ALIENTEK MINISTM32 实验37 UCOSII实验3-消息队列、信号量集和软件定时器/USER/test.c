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
//ALIENTEK MiniSTM32������ʵ��37
//UCOSIIʵ��3-��Ϣ���С��ź������������ʱ�� 
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
 			   
//LED����
//�����������ȼ�
#define LED_TASK_PRIO       			7 
//���������ջ��С
#define LED_STK_SIZE  		    		64
//�����ջ
OS_STK LED_TASK_STK[LED_STK_SIZE];
//������
void led_task(void *pdata);

//����������
//�����������ȼ�
#define TOUCH_TASK_PRIO       		 	6
//���������ջ��С
#define TOUCH_STK_SIZE  				128
//�����ջ	
OS_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//������
void touch_task(void *pdata);

//������Ϣ��ʾ����
//�����������ȼ�
#define QMSGSHOW_TASK_PRIO    			5 
//���������ջ��С
#define QMSGSHOW_STK_SIZE  		 		64
//�����ջ	
OS_STK QMSGSHOW_TASK_STK[QMSGSHOW_STK_SIZE];
//������
void qmsgshow_task(void *pdata);


//������
//�����������ȼ�
#define MAIN_TASK_PRIO       			4 
//���������ջ��С
#define MAIN_STK_SIZE  					128
//�����ջ	
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];
//������
void main_task(void *pdata);

//�ź���������
//�����������ȼ�
#define FLAGS_TASK_PRIO       			3 
//���������ջ��С
#define FLAGS_STK_SIZE  		 		64
//�����ջ	
OS_STK FLAGS_TASK_STK[FLAGS_STK_SIZE];
//������
void flags_task(void *pdata);


//����ɨ������
//�����������ȼ�
#define KEY_TASK_PRIO       			2 
//���������ջ��С
#define KEY_STK_SIZE  					64
//�����ջ	
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//������
void key_task(void *pdata);
//////////////////////////////////////////////////////////////////////////////
    
OS_EVENT * msg_key;			//���������¼���	  
OS_EVENT * q_msg;			//��Ϣ����
OS_TMR   * tmr1;			//�����ʱ��1
OS_TMR   * tmr2;			//�����ʱ��2
OS_TMR   * tmr3;			//�����ʱ��3
OS_FLAG_GRP * flags_key;	//�����ź�����
void * MsgGrp[256];			//��Ϣ���д洢��ַ,���֧��256����Ϣ

//�����ʱ��1�Ļص�����	
//ÿ100msִ��һ��,������ʾCPUʹ���ʺ��ڴ�ʹ����		   
void tmr1_callback(OS_TMR *ptmr,void *p_arg) 
{
 	static u16 cpuusage=0;
	static u8 tcnt=0;	    
	POINT_COLOR=BLUE;
	if(tcnt==5)
	{
 		LCD_ShowxNum(182,10,cpuusage/5,3,16,0);			//��ʾCPUʹ����  
		cpuusage=0;
		tcnt=0; 
	}
	cpuusage+=OSCPUUsage;
	tcnt++;				    
 	LCD_ShowxNum(182,30,mem_perused(),3,16,0);	//��ʾ�ڴ�ʹ����	 	  		 					    
	LCD_ShowxNum(182,50,((OS_Q*)(q_msg->OSEventPtr))->OSQEntries,3,16,0X80);//��ʾ���е�ǰ�Ĵ�С		   
 }

//�����ʱ��2�Ļص�����				  	   
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
//�����ʱ��3�Ļص�����				  	   
void tmr3_callback(OS_TMR *ptmr,void *p_arg) 
{	
	u8* p;	 
	u8 err; 
	static u8 msg_cnt=0;	//msg���	  
	p=mymalloc(13);	//����13���ֽڵ��ڴ�
	if(p)
	{
	 	sprintf((char*)p,"ALIENTEK %03d",msg_cnt);
		msg_cnt++;
		err=OSQPost(q_msg,p);	//���Ͷ���
		if(err!=OS_ERR_NONE) 	//����ʧ��
		{
			myfree(p);	//�ͷ��ڴ�
			OSTmrStop(tmr3,OS_TMR_OPT_NONE,0,&err);	//�ر������ʱ��3
 		}
	}
} 
//����������   
void ucos_load_main_ui(void)
{
	LCD_Clear(WHITE);	//����
 	POINT_COLOR=RED;	//��������Ϊ��ɫ 
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
		    
 	LCD_ShowString(5,125,240,16,16,"QUEUE MSG");//������Ϣ
	LCD_ShowString(5,150,240,16,16,"Message:");	 
	LCD_ShowString(5+120,125,240,16,16,"FLAGS");//�ź�����
	LCD_ShowString(5,225,240,16,16,"TOUCH");	//������
	LCD_ShowString(5+120,225,240,16,16,"TMR2");	//������Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
  	LCD_ShowString(150,10,200,16,16,"CPU:   %");	
   	LCD_ShowString(150,30,200,16,16,"MEM:   %");	
   	LCD_ShowString(150,50,200,16,16," Q :000");	

	delay_ms(300);
}	 
											   
int main(void)
{		
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 
	KEY_Init();				//������ʼ��   
	mem_init();				//��ʼ���ڴ��
   	tp_dev.init();
	ucos_load_main_ui(); 
	OSInit();  	 			//��ʼ��UCOSII
  	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
	OSStart();	    
}							    

//��ʼ����
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	u8 err;	    	    
	pdata = pdata; 	
	msg_key=OSMboxCreate((void*)0);		//������Ϣ����
	q_msg=OSQCreate(&MsgGrp[0],256);	//������Ϣ����
 	flags_key=OSFlagCreate(0,&err); 	//�����ź�����		  
	  
	OSStatInit();					//��ʼ��ͳ������.�������ʱ1��������	
 	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
 	OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);						   
 	OSTaskCreate(touch_task,(void *)0,(OS_STK*)&TOUCH_TASK_STK[TOUCH_STK_SIZE-1],TOUCH_TASK_PRIO);	 				   
 	OSTaskCreate(qmsgshow_task,(void *)0,(OS_STK*)&QMSGSHOW_TASK_STK[QMSGSHOW_STK_SIZE-1],QMSGSHOW_TASK_PRIO);	 				   
 	OSTaskCreate(main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_STK_SIZE-1],MAIN_TASK_PRIO);	 				   
 	OSTaskCreate(flags_task,(void *)0,(OS_STK*)&FLAGS_TASK_STK[FLAGS_STK_SIZE-1],FLAGS_TASK_PRIO);	 				   
 	OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	 				   
 	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}
//LED����
void led_task(void *pdata)
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
//����������
void touch_task(void *pdata)
{	  	
	while(1)
	{
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)		//������������
		{	
		 	if(tp_dev.x[0]<120&&tp_dev.y[0]<lcddev.height&&tp_dev.y[0]>220)
			{													   
				TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],BLUE);		//��ͼ	 
				delay_ms(2); 			   
			}
		}else delay_ms(10);	//û�а������µ�ʱ�� 
	}
}     
//������Ϣ��ʾ����
void qmsgshow_task(void *pdata)
{
	u8 *p;
	u8 err;
	while(1)
	{
		p=OSQPend(q_msg,0,&err);//������Ϣ����
		LCD_ShowString(5,170,240,16,16,p);//��ʾ��Ϣ
 		myfree(p);	  
		delay_ms(500);	 
	}									 
}
//������
void main_task(void *pdata)
{							 
	u32 key=0;	
	u8 err;	
 	u8 tmr2sta=1;	//�����ʱ��2����״̬   
 	u8 tmr3sta=0;	//�����ʱ��3����״̬
	u8 flagsclrt=0;	//�ź�������ʾ���㵹��ʱ   
 	tmr1=OSTmrCreate(10,10,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,0,"tmr1",&err);		//100msִ��һ��
	tmr2=OSTmrCreate(10,20,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr2_callback,0,"tmr2",&err);		//200msִ��һ��
	tmr3=OSTmrCreate(10,10,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr3_callback,0,"tmr3",&err);		//100msִ��һ��
	OSTmrStart(tmr1,&err);//���������ʱ��1				 
	OSTmrStart(tmr2,&err);//���������ʱ��2				 
 	while(1)
	{
		key=(u32)OSMboxPend(msg_key,10,&err); 
		if(key)
		{
			flagsclrt=51;//500ms�����
			OSFlagPost(flags_key,1<<(key-1),OS_FLAG_SET,&err);//���ö�Ӧ���ź���Ϊ1
		}
		if(flagsclrt)//����ʱ
		{
			flagsclrt--;
			if(flagsclrt==1)LCD_Fill(140,162,239,162+16,WHITE);//�����ʾ
		}
		switch(key)
		{ 
			case KEY0_PRES://�����ʱ��3����	 
				tmr3sta=!tmr3sta;
				if(tmr3sta)OSTmrStart(tmr3,&err);  
				else OSTmrStop(tmr3,OS_TMR_OPT_NONE,0,&err);		//�ر������ʱ��3
 				break; 
			case KEY1_PRES://�����ʱ��2����&�����������
				tmr2sta=!tmr2sta;
				if(tmr2sta)OSTmrStart(tmr2,&err);			  	//���������ʱ��2
				else 
				{		    		    
  					OSTmrStop(tmr2,OS_TMR_OPT_NONE,0,&err);	//�ر������ʱ��2
 					LCD_ShowString(148,262,240,16,16,"TMR2 STOP");//��ʾ��ʱ��2�ر���	
				}
				LCD_Fill(0,221,120-1,lcddev.height-1,WHITE);//�����������
				break;	
			case WKUP_PRES://У׼
				OSTaskSuspend(TOUCH_TASK_PRIO);						//������������		 
				OSTaskSuspend(QMSGSHOW_TASK_PRIO);	 				//���������Ϣ��ʾ����		 
 				OSTmrStop(tmr1,OS_TMR_OPT_NONE,0,&err);				//�ر������ʱ��1
				if(tmr2sta)OSTmrStop(tmr2,OS_TMR_OPT_NONE,0,&err);	//�ر������ʱ��2				 
 				if((tp_dev.touchtype&0X80)==0)TP_Adjust();	 
				OSTmrStart(tmr1,&err);				//���¿��������ʱ��1
				if(tmr2sta)OSTmrStart(tmr2,&err);	//���¿��������ʱ��2	 
 				OSTaskResume(TOUCH_TASK_PRIO);		//���
 				OSTaskResume(QMSGSHOW_TASK_PRIO); 	//���
				ucos_load_main_ui();				//���¼���������		 
				break;			 
				
		}  
		delay_ms(10);
	}
}		   
//�ź�������������
void flags_task(void *pdata)
{	
	u16 flags;	
	u8 err;	    						 
	while(1)
	{
		flags=OSFlagPend(flags_key,0X001F,OS_FLAG_WAIT_SET_ANY,0,&err);//�ȴ��ź���
		if(flags&0X0001)LCD_ShowString(140,162,240,16,16,"KEY0 DOWN  "); 
		if(flags&0X0002)LCD_ShowString(140,162,240,16,16,"KEY1 DOWN  "); 
		if(flags&0X0004)LCD_ShowString(140,162,240,16,16,"KEY_UP DOWN"); 
		LED1=0;
		delay_ms(50);
		LED1=1;
		OSFlagPost(flags_key,0X0007,OS_FLAG_CLR,&err);//ȫ���ź�������
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









