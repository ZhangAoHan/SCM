#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "Motor.h"	
#include "Oled.h"	
#include "Timer3.h"
#include "Control.h"

void OLED_Display_Speed(int x,int y);
void OLED_Display(int x,int y);
void Bluetooth(void);		

float Angle_Balance;
float Gyro_Balance;
int Moto1,Moto2; 
int left,right;
u8 i;
u8 res;           //蓝牙接收变量
int main(void)
{

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600

	OLED_Init();
	OLED_Clear();
	
	PWM_Init(7199,0);   //pwm满值=7200，频率=10K
	Motor_Init();  
	Encoder_Init_TIM4();
	Encoder_Init_TIM2();
	
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();
	
	TIME3_init();  //计数频率=10k  每5ms中断一次
		
  	while(1)
	{

		Bluetooth();			
	}	 
} 


void OLED_Display_Speed(int x,int y)
{
//	OLED_ShowChar(0,0,'a',16);  // x*y 8=6*8  16=8*16   y=y*8
//	OLED_ShowNum(8,2,10,2,16);
//	OLED_ShowString(16,4,"my",16);
//	OLED_ShowCHinese(24,6,3); 
	OLED_ShowString(0,0,"L",16);
	OLED_ShowChar(8,0,':',16);
	OLED_ShowNum(16,0,x,14,16);
	
	OLED_ShowString(0,2,"R",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,y,14,16);
	
}
void OLED_Display(int x,int y)
{
	OLED_ShowCHinese(0,0,14);
	OLED_ShowCHinese(16,0,15);
	OLED_ShowCHinese(32,0,16);
	OLED_ShowChar(120,0,' ',16);
	
	OLED_ShowString(0,2,"L",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,x,6,16);
	
	OLED_ShowString(64,2,"R",16);
	OLED_ShowChar(72,2,':',16);
	OLED_ShowNum(80,2,y,6,16);
}

void Bluetooth()          //蓝牙接收函数
{
	switch(res)
	{
		case 0x00:  if(left<0) left=-left; if(right<0) right=-right; OLED_Display_Speed(left,right);   break;
		case 0x01:  if(left<0) left=-left; if(right<0) right=-right; OLED_Display(left,right);   break;
	}
}

