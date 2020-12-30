#include "motor_control.h"
#include "motor.h"
#include "delay.h"
#include "led.h"
extern u8 use_start;

void motor_up(void)
{
		PWMA=500;
		AIN1=1;  
		AIN2=0;
}
void motor_down(void)
{
		PWMA=500;
		AIN1=0;  //下降
		AIN2=1;
}

void motor_stop(void)
{
		AIN1=0; 
		AIN2=0;
}

u8 motor_init(void)
{
	if(KEY_DOWN==1)
	{
		motor_down();
		return 1;
	}
	else 
	{
		motor_stop();
		return 0;
	}
}
void use_touch_scan(void)
{
	if(KEY_TOUCH==1&&use_start==0)
	{
		use_start=1;
		delay_ms(200);
	}
	else if(KEY_TOUCH==1&&use_start==1)
	{
		use_start=0;
		delay_ms(200);
	}
}
void use_motor_control(u8 lc)    // 楼层     存车 取车的电机控制函数。
{
	
	if(lc==1)   //要去一楼
	{
		if(use_start==1)
		{
			PWM=8;     //开门杆
		}
		else
		{
			PWM=18;    //关门
		}
	}
	else if(lc==2)   //要去二楼
	{
		if(use_start==1)   //需要上升
		{
			if(KEY_UP==1)
			{
				motor_up();
			}
			else
			{
				motor_stop();
				PWM=8;     //开门
			}
		}
		else          //需要下降或者还没启动
		{
			if(KEY_DOWN==1) //需要下降
			{
				motor_down();
				PWM=18; 
			}
			else         //还没启动需要上升或者已经下降完成
			{
				motor_stop();
			}
		}
	}
}






















