#include "motor_control.h"
#include "led.h"
#include "motor.h"
#include "lcd.h"
#include "text.h"	
#include "delay.h"	 


extern u8 use_start;   //按键启动标准量
 extern u8 dl_success;   //正在进行停车操作的标准量  1正在进行  0操作完成  为了显示 正在停车操作或者显示正在取车操作
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


u8 motor_rest(void)           //电梯复位
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

void use_touch_scan(void)     // use_start=0  还没开始  use_start=1 开始  use_start=2  结束   //结束后需要清理
{
	if(KEY_TOUCH==1&&use_start==0)
	{
		use_start=1;
	}
	else if(KEY_TOUCH==1&&use_start==1)
	{
		use_start=2;    //结束标志
	}
}

void use_motor_control(u8 lc)             //停车及取车操作，完成标准为dl_success=1
{
		if(lc==1)
	{
		if(KEY_DOWN==0&&use_start==1)   //存车或者取车
		{
			PWM=8;    //开门
		}
		else if(KEY_DOWN==0&&use_start==2)   //存车完成或者取车完成
		{
			PWM=18;   
			use_start=0;
			dl_success=0;
		}
		
	}
	else if(lc==2)
	{
		if(KEY_UP==1&&use_start==1)  //启动  但是没到2楼   //此时KEY_DOWN=0
		{
			motor_up();
		}
		else if(KEY_UP==0&&use_start==1)  //已启动  也到了2楼    
		{
			motor_stop();
			PWM=8; 
		}
		else if(KEY_DOWN==1&&use_start==2)    //再按一下 开始下降  直到底下的触碰开关碰到为止
		{
			PWM=18;   
			motor_down();
		}
		else if(KEY_DOWN==0&&use_start==2)   //操作完成
		{
			motor_stop();
			dl_success=0;
			use_start=0;

		}
//		else  //其余情况  都为非法操作  停止
//		{
//			motor_stop();
//			Show_Str_Mid(0,150,"feifa",24,240);
//		}

	}
	
	
}

void cl_display(u8 lc,u8 s)   //停车 或者取车操作显示界面及控制  选完停车位直接调用即可   
{
	if(s==1)            //存车
	{
		LCD_Clear(WHITE); 
		delay_ms(50);
		Show_Str_Mid(0,150,"用户正在进行",24,240);
		Show_Str_Mid(0,180,"存车操作",24,240);	
		dl_success=1;
	}
	else if(s==2)        //取车
	{
		LCD_Clear(WHITE); 
		delay_ms(50);
		Show_Str_Mid(0,150,"用户正在进行",24,240);
		Show_Str_Mid(0,180,"取车操作",24,240);	
		dl_success=1;
	}
	use_start=0;
	while(dl_success)
	{
		use_motor_control(lc);
	}
}






