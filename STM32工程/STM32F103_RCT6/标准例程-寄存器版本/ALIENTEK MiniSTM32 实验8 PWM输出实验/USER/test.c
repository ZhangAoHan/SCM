#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "timer.h" 
//ALIENTEK Mini STM32开发板范例代码8
//PWM输出实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{			
 	u16 led0pwmval=0;    
	u8 dir=1;	
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
	TIM1_PWM_Init(899,0);//不分频。PWM频率=72000/(899+1)=80Khz 
   	while(1)
	{
 		delay_ms(10);	 
		if(dir)led0pwmval++;
		else led0pwmval--;	 
 		if(led0pwmval>300)dir=0;
		if(led0pwmval==0)dir=1;	   					 
		LED0_PWM_VAL=led0pwmval;	   
	} 
}














