#include "control.h"
#include "io_control.h"
#include "delay.h"	
#include "motor.h"
#include "24l01.h"
#include "timer.h"



extern u8 tmp_buf[33];
extern u8 lc;  //¥����
extern u8 start;  
void use_control(void)
{
	Nrf_communicate();
	if(tmp_buf[0]=='S')  //��Ч��Ϣ��ͷΪS  ��Ч��Ϣ��ͷΪN
	{
		if(start==1)     //����  ��һ��
		{
			if(lc==2)    //��Ҫ�ϵ�����  ����������һ¥
			{
				if(KEY_UP==1) //�����Ǹ�����û�б�����
				{
					motor_up();
				}
				else if(KEY_UP==0)  //�Ѿ����˶�¥
				{
					motor_STOP();
					PWM=10;             //����
				}
			
			}
			if(lc==1)
			{
				PWM=10;   //����
			}
			
			}
		
		else if(start==2)          //�ڶ���
		{ 
			if(lc==2)   //�Ӷ�¥�µ�1¥
			{
				if(KEY_DOWN==1)   //�����ڶ�¥
				{
					if(KEY_UP==0)
					{
						PWM=5;   //����
					}
					motor_DOWN();
				}
				else if(KEY_DOWN==0)   //�Ѿ��µ���1¥
				{
					motor_STOP();
					start=0;
				}
			}
			if(lc==1)  
			{
				PWM=5; 
				start=0;
			}
		}
	}
//	if(KEY_UP==0||KEY_DOWN==0)
//	{
//		LED_RED=1;
//		LED_GREEN=0;

//	}
//	else
//	{
//		LED_RED=0;
//		LED_GREEN=0;

//	}
}
	
void motor_up(void)
{
	PWMA=500;
	AIN1=1;
	AIN2=0;
}
void motor_DOWN(void)
{
	PWMA=500;
	AIN1=0;
	AIN2=1;
}
void motor_STOP(void)
{
	PWMA=0;
	AIN1=0;
	AIN2=0;
}
void Nrf_communicate(void)
{
	u8 t;
	if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
	{
		for(t=1;t<31;t++)
		{
			tmp_buf[t]=tmp_buf[t]-48;
		}
		lc=tmp_buf[1];
		
	}
		
}

void state_scan(void)
{
	if(KEY_START==1&&start==0)   //��һ�� 
	{
		start=1;
	}
	if(KEY_START==1&&start==1)   //�ڶ���
	{
		start=2;
	}
	if(start>=3)
	{
		start=0;
	}
	
}

void user_motor_init(void)        //�����λ
{
	while(KEY_DOWN)
	{
		motor_DOWN();
	}
}






