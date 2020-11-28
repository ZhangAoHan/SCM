#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "timer.h"
#include "C.h"
u32 Distance;                               //超声波测距
void Dj(void);
int main(void)
{				 
//	u8 t=0; 
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,9600); 	//串口初始化为9600
	PWM_Init(200,7199);      //舵机控制需要20ms的脉冲即50HZ    50=72 000 000/psc*arr  
	
	TIM2_Init(65535,71);
  	while(1)
	{
		Read_Distane();
		printf("Distance:%d\r\n",Distance);
	Dj();

	}	 
} 


void Dj()
{	
	PWM=12;    //中值
	delay_ms(1000);
	 PWM=9;    //偏25°左右
	delay_ms(1000);
		PWM=12;    //中值
	delay_ms(1000);
	 PWM=15;    //偏25°左右
	delay_ms(1000);
}



