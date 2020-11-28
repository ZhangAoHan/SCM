#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "Motor.h"	
#include "Oled.h"	


void OLED_display(u16 x,u16 y);
void Motor(void);


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
	
	
  	while(1)
	{
		Motor();
	}	 
} 


void OLED_display(u16 x,u16 y)
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


