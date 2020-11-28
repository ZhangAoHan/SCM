#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "Motor.h"	
#include "Oled.h"	
#include "Timer3.h"
#include "Control.h"

void OLED_display(int x,int y);
void Motor(void);
void Motor_Back(void);
void Motor_Go(void);
		

float Angle_Balance;
float Gyro_Balance;
int Moto1,Moto2; 
int left,right;
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
	left=Read_Encoder(2);
	right=Read_Encoder(4);
	OLED_display(left,right);
	}	 
} 


void OLED_display(int x,int y)
{
//	OLED_ShowChar(0,0,'a',16);  // x*y 8=6*8  16=8*16   y=y*8
//	OLED_ShowNum(8,2,10,2,16);
//	OLED_ShowString(16,4,"my",16);
//	OLED_ShowCHinese(24,6,3); 
	OLED_ShowString(0,0,"L",16);
	OLED_ShowChar(8,0,':',16);
	OLED_ShowNum(16,0,x,2,16);
	
	OLED_ShowString(0,2,"R",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,y,2,16);
	
}
void Motor()
{
	u16 left,right;
	AIN1=0;
	AIN2=1;
	PWMA=2000;
	BIN1=1;
	BIN2=0;
	PWMB=2000;
	
	left=Read_Encoder(2);
	right=Read_Encoder(4);
	OLED_display(left,right);
}
void Motor_Go()
{
	int left,right;
	AIN1=1;
	AIN2=0;
	PWMA=3000;
	left=Read_Encoder(2);
	BIN1=0;
	BIN2=1;
	PWMB=2000;

	right=Read_Encoder(4);
	OLED_display(left,right);
}
void Motor_Back()
{
	int left,right;
	AIN1=0;
	AIN2=1;
	PWMA=3000;
	left=Read_Encoder(2);
	BIN1=1;
	BIN2=0;
	PWMB=2500;

	right=Read_Encoder(4);
	OLED_display(left,right);
}


