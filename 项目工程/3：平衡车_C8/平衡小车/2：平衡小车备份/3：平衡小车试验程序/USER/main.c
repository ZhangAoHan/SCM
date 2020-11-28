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
void OLED_Display_Init(void);
void BlueTooth(void);

 int main(void)
 {	
	/* 系统函数初始化 */
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600
	 
	 /* Oled显示初始化函数 */
	OLED_Init();
	OLED_Clear();
	OLED_Display_Init();
	 delay_ms(2000);
    /* 电机控制函数初始化 */	 
	PWM_Init(7199,0);   //pwm满值=7200，频率=10K
	Motor_Init();  
	Encoder_Init_TIM4();
	Encoder_Init_TIM2();
	 
	 /* MPU6050初始化函数 */
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();
	 
	 /* 控制函数初始化 */
	 TIME3_init();
	 
	 OLED_Clear();   //清屏
	 
	while(1)
	{
	BlueTooth();
	}
 }
void OLED_Display_Init()     //初始化显示  Team of flame
{	
   OLED_ShowString(8,2,"Team Of Flame",16);
}
void OLED_Display(int x,int y)     //停止
{	
	if(x>0) x=x;
	if(x<0) x=-x;
	if(y>0) y=y;
	if(y<0) y=-y;
	OLED_ShowString(0,2,"L",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,x,4,16);
	
	OLED_ShowString(0,4,"R",16);
	OLED_ShowChar(8,4,':',16);
	OLED_ShowNum(16,4,y,4,16);
}
void BlueTooth()
{
	switch(res)
	{
		case 0x00: OLED_ShowString(0,0,"Stop",16);OLED_Display(left,right);Flag_Left=0;Flag_Right=0;Motor=0;  Motor_Control();   break;   //停止
		case 0x01: OLED_ShowString(0,0,"Fall Back",16);OLED_Display(left,right);Flag_Left=0;Flag_Right=0;Motor=20; Motor_Control();   break;   //后退
		case 0x02: OLED_ShowString(0,0,"Go Forward",16);OLED_Display(left,right);Flag_Left=0;Flag_Right=0;Motor=-20;Motor_Control();   break;   //前进
		case 0x03: OLED_ShowString(0,0,"Left",16);OLED_Display(left,right);Flag_Left=1;Flag_Right=0;Motor=0;  Motor_Control();   break;   //左转
		case 0x04: OLED_ShowString(0,0,"Right",16);OLED_Display(left,right);Flag_Left=0;Flag_Right=1;Motor=0;  Motor_Control();   break;   //右转

		
	}
}

