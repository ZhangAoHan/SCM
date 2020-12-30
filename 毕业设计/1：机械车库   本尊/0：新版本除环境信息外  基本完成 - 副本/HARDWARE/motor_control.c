#include "motor_control.h"
#include "led.h"
#include "motor.h"
#include "lcd.h"
#include "text.h"	
#include "delay.h"	 


extern u8 use_start;   //����������׼��
 extern u8 dl_success;   //���ڽ���ͣ�������ı�׼��  1���ڽ���  0�������  Ϊ����ʾ ����ͣ������������ʾ����ȡ������
void motor_up(void)
{
		PWMA=500;
		AIN1=1;
		AIN2=0;
}
void motor_down(void)
{
	PWMA=500;
	AIN1=0;
	AIN2=1;
}
void motor_stop(void)
{
	AIN1=0;
	AIN2=0;
}


u8 motor_rest(void)           //���ݸ�λ
{
	if(KEY_DOWN==1)
	{
		motor_down();
		return 1;
	}
	else 
	{
		motor_stop();
		PWM=18;  
		return 0;
	}
}

void use_touch_scan(void)     // use_start=0  ��û��ʼ  use_start=1 ��ʼ  use_start=2  ����   //��������Ҫ����
{
	if(KEY_TOUCH==1&&use_start==0)
	{
		use_start=1;
	}
	else if(KEY_TOUCH==1&&use_start==1)
	{
		use_start=2;    //������־
	}
}

void use_motor_control(u8 lc)             //ͣ����ȡ����������ɱ�׼Ϊdl_success=1
{
		if(lc==1)
	{
		if(KEY_DOWN==0&&use_start==1)   //�泵����ȡ��
		{
			PWM=8;    //����
		}
		else if(KEY_DOWN==0&&use_start==2)   //�泵��ɻ���ȡ�����
		{
			PWM=18;   
			use_start=0;
			dl_success=0;
		}
		
	}
	else if(lc==2)
	{
		if(KEY_UP==1&&use_start==1)  //����  ����û��2¥   //��ʱKEY_DOWN=0
		{
			motor_up();
		}
		else if(KEY_UP==0&&use_start==1)  //������  Ҳ����2¥    
		{
			motor_stop();
			PWM=8; 
		}
		else if(KEY_DOWN==1&&use_start==2)    //�ٰ�һ�� ��ʼ�½�  ֱ�����µĴ�����������Ϊֹ
		{
			PWM=18;   
			motor_down();
		}
		else if(KEY_DOWN==0&&use_start==2)   //�������
		{
			motor_stop();
			dl_success=0;
			use_start=0;

		}
//		else  //�������  ��Ϊ�Ƿ�����  ֹͣ
//		{
//			motor_stop();
//			Show_Str_Mid(0,150,"feifa",24,240);
//		}

	}
	
	
}

void cl_display(u8 lc,u8 s)   //ͣ�� ����ȡ��������ʾ���漰����  ѡ��ͣ��λֱ�ӵ��ü���   
{
	if(s==1)            //�泵
	{
		LCD_Clear(WHITE); 
		delay_ms(50);
		Show_Str_Mid(0,150,"�û����ڽ���",24,240);
		Show_Str_Mid(0,180,"�泵����",24,240);	
		dl_success=1;
	}
	else if(s==2)        //ȡ��
	{
		LCD_Clear(WHITE); 
		delay_ms(50);
		Show_Str_Mid(0,150,"�û����ڽ���",24,240);
		Show_Str_Mid(0,180,"ȡ������",24,240);	
		dl_success=1;
	}
	use_start=0;
	while(dl_success)
	{
		use_motor_control(lc);
	}
}






