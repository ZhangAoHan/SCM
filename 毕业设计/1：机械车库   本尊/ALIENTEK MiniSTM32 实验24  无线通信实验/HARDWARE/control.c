#include "control.h"
#include "io_control.h"
#include "delay.h"	
#include "motor.h"
#include "24l01.h"
#include "timer.h"



extern u8 tmp_buf[33];
extern u8 lc;  //楼层信
extern u8 start;  
void use_control(void)
{
	Nrf_communicate();
	if(tmp_buf[0]=='S')  //有效信息开头为S  无效信息开头为N
	{
		if(start==1)     //启动  第一步
		{
			if(lc==2)    //需要上到二层  但是现在在一楼
			{
				if(KEY_UP==1) //上面那个按键没有被触发
				{
					motor_up();
				}
				else if(KEY_UP==0)  //已经到了二楼
				{
					motor_STOP();
					PWM=10;             //开门
				}
			
			}
			if(lc==1)
			{
				PWM=10;   //开门
			}
			
			}
		
		else if(start==2)          //第二步
		{ 
			if(lc==2)   //从二楼下到1楼
			{
				if(KEY_DOWN==1)   //现在在二楼
				{
					if(KEY_UP==0)
					{
						PWM=5;   //关门
					}
					motor_DOWN();
				}
				else if(KEY_DOWN==0)   //已经下到了1楼
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
	if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
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
	if(KEY_START==1&&start==0)   //第一步 
	{
		start=1;
	}
	if(KEY_START==1&&start==1)   //第二部
	{
		start=2;
	}
	if(start>=3)
	{
		start=0;
	}
	
}

void user_motor_init(void)        //电机复位
{
	while(KEY_DOWN)
	{
		motor_DOWN();
	}
}






