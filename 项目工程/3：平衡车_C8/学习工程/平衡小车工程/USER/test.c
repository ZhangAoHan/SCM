#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "Motor.h"	
#include "Oled.h"	

int main(void)
{

	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600

	PWM_Init(7199,0);    //电机控制函数（PWM满值为7200，频率为10k）
	Motor_Init();
	
  	while(1)
	{

	}	 
} 






