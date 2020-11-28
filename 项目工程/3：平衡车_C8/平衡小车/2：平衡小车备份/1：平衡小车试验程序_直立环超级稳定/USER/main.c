#include "sys.h"
#include "Motor.h" 
#include "Oled.h"	
#include "Timer.h"
#include "Control.h"

u8 res;           //蓝牙接收变量
float Angle_Balance,Gyro_Balance;
int left,right;
int Moto1,Moto2; 
void OLED_Display(float x,float y);
 int main(void)
 {	
	/* 系统函数初始化 */
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600
	 
    /* 电机控制函数初始化 */	 
	PWM_Init(7199,0);   //pwm满值=7200，频率=10K
	Motor_Init();  
	Encoder_Init_TIM4();
	Encoder_Init_TIM2();
	 
	/* Oled显示初始化函数 */
	OLED_Init();
	OLED_Clear();
	 
	 /* MPU6050初始化函数 */
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();
	 
	 /* 控制函数初始化 */
	 TIME3_init();
	 
	 
	while(1)
	{
		Motor_Control();
	}
 }

void OLED_Display(float x,float y)
{	
	OLED_ShowString(0,0,"L",16);
	OLED_ShowChar(8,0,':',16);
	OLED_ShowNum(16,0,x,14,16);
	
	OLED_ShowString(0,2,"R",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,y,14,16);
	
	

}


