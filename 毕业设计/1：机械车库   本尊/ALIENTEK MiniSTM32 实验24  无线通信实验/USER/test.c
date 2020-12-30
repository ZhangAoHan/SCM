#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "24l01.h" 
#include "control.h"
#include "motor.h"
#include "timer.h"
#include "motor.h"
#include "io_control.h"
u8 tmp_buf[33]; 
 u8 lc;  //楼层信
 u8 start;  

int main(void)
{		
			 

 	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
// 	NRF24L01_Init();    	//初始化NRF24L01  	
	

	PWM_Init(999,0);   //pwm满值=7200，频率=10K
	TIM3_Int_Init(4999,7199);
	Io_init();
// 	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
//	{;}	
	DJ_PWM_Init(200,7199);       //控制舵机
	NRF24L01_RX_Mode();		
//	user_motor_init();
	
while(1)
{

	use_control();
	
}
	
}



















