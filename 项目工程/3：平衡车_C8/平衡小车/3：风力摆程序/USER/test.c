#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "Motor.h"

int main(void)
{			
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	TIME3_PWM_init(0,7199);   //PWM频率为72M/7200=10Khz
	IO_init();
   	while(1)
	{
		Motor1Vcc=1;
		Motor1Gnd=0;
		Motor1=7000;
		
//		Motor2Vcc=0;
//		Motor2Gnd=1;
//		Motor2=7200;
	} 
}














