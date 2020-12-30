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
		AIN1=0;  //�½�
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
void use_motor_control(u8 lc)    // ¥��     �泵 ȡ���ĵ�����ƺ�����
{
	
	if(lc==1)   //Ҫȥһ¥
	{
		if(use_start==1)
		{
			PWM=8;     //���Ÿ�
		}
		else
		{
			PWM=18;    //����
		}
	}
	else if(lc==2)   //Ҫȥ��¥
	{
		if(use_start==1)   //��Ҫ����
		{
			if(KEY_UP==1)
			{
				motor_up();
			}
			else
			{
				motor_stop();
				PWM=8;     //����
			}
		}
		else          //��Ҫ�½����߻�û����
		{
			if(KEY_DOWN==1) //��Ҫ�½�
			{
				motor_down();
				PWM=18; 
			}
			else         //��û������Ҫ���������Ѿ��½����
			{
				motor_stop();
			}
		}
	}
}






















