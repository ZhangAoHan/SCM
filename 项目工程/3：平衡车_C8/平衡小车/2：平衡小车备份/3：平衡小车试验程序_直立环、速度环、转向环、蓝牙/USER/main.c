#include "sys.h"
#include "Motor.h" 
#include "Oled.h"	
#include "Timer.h"
#include "Control.h"
#include "Motor.h"   
u8 res;           //蓝牙接收变量
int 	Motor=0x00;
float Angle_Balance,Gyro_Balance,Gyro_Turn;
int left,right;
int Moto1,Moto2; 
int Flag_Left=0,Flag_Right=0;
void OLED_Display(int x,int y);
void BlueTooth(void);
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
	OLED_Display(left,right);
	BlueTooth();
	}
 }

void OLED_Display(int x,int y)
{	
	if(x>0) x=x;
	if(x<0) x=-x;
	if(y>0) y=y;
	if(y<0) y=-y;
	OLED_ShowString(0,0,"L",16);
	OLED_ShowChar(8,0,':',16);
	OLED_ShowNum(16,0,x,14,16);
	
	OLED_ShowString(0,2,"R",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,y,14,16);
}

void BlueTooth()
{
	switch(res)
	{
		case 0x00:Flag_Left=0;Flag_Right=0;Motor=0;Motor_Control();   break;
		case 0x01:Flag_Left=0;Flag_Right=0;Motor=20;Motor_Control();  break;
		case 0x02:Flag_Left=0;Flag_Right=0;Motor=-20;Motor_Control(); break;
		case 0x03:Flag_Left=1;Flag_Right=0;Motor=0;Motor_Control(); break;
		case 0x04:Flag_Left=0;Flag_Right=1;Motor=0;Motor_Control(); break;

		
	}
}
