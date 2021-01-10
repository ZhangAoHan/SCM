/*-------------------------------------
	      ��ʱ���ó���
����us,ms,ʱ�ӳ�ʼ�����ڱ������ܹ����
�Ѿ����⼸�������װ�ɿ�,��������ʹ��
		  2013��7��22��
-------------------------------------*/
  #define UCOS_DELAY_OPEN		  //��ʱѡ�񿪹�
//#define NO_UCOS_DELAY_OPEN

#include "delay.h"
#include "misc.h"
#include "stm32f10x.h"

/*-------------------------------------
	 	   �������ʱ 
-------------------------------------*/
#ifdef NO_UCOS_DELAY_OPEN
unsigned int TimeDelay;	 //������ȫ�ֱ���

void DelayInit(void)
{
	if(SysTick_Config(SystemCoreClock / 1000000)) //����Ϊ1usһ���ж�
	{
		while(1);  	//�������ʧ������ѭ��
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  //ʧ�ܵδ�ʱ��
}

void delayus(unsigned int us)
{
	TimeDelay = us;	 						   //us��ֵ��ȫ�ֱ���TD
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  //ʹ�ܵδ�ʱ��
	while(TimeDelay != 0);					   //���ж����Լ�
}	

void delayms(unsigned int ms)
{
	delayus(ms * 1000);		//1ms = 1000us
}

void SysTick_Handler(void)						//���ж����Լ�
{
	if (TimeDelay != 0)
	{ 
		TimeDelay--;
	}	
}
#endif
/*-------------------------------------
	 	   ��ϵͳ����ʱ 
-------------------------------------*/
#ifdef UCOS_DELAY_OPEN

#include "ucos_ii.h"
unsigned int reload;
static unsigned char  fac_us=0;
static unsigned short int fac_ms=0;

void DelayInit()
{	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us = SystemCoreClock/8000000;	//Ϊϵͳʱ�ӵ�1/8 
	
	reload=SystemCoreClock/8000000;		//ÿ���ӵļ������� ��λΪK	   
	reload*=1000000/OS_TICKS_PER_SEC;						
	fac_ms=1000/OS_TICKS_PER_SEC;		//����ucos������ʱ�����ٵ�λ	   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   
	SysTick->LOAD=reload; 		
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;	
}

void SysTick_Handler(void)	  //ʹ��UCOSʱ
{				   
	OSIntEnter();		
    OSTimeTick();                   
    OSIntExit();        
}

void delayus(unsigned int nus)
{		
	unsigned int ticks;
	unsigned int told,tnow,tcnt=0;
	unsigned int reload=SysTick->LOAD;	//LOAD��ֵ	    	 
	ticks=nus*fac_us; 			//��Ҫ�Ľ�����	  		 
	tcnt=0;
	told=SysTick->VAL;        	//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	}; 									    
}

void delayms(unsigned int nms)
{	
	if(OSRunning==TRUE)//���os�Ѿ�������	    
	{		  
		if(nms>=fac_ms)//��ʱ��ʱ�����ucos������ʱ������ 
		{
   			OSTimeDly(nms/fac_ms);//ucos��ʱ
		}
		nms%=fac_ms;				//ucos�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
	}
	delayus((unsigned int)(nms*1000));	//��ͨ��ʽ��ʱ,��ʱucos�޷���������.
}
#endif

void Software_Delay(unsigned int sec)
{
	for(;sec>0;sec--);
}
