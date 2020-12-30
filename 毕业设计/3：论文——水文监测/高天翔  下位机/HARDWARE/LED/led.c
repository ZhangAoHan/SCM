#include "led.h"

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA,PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PA.8 端口配置（使用的是A8脚）
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8(上面已经将参赛的设定放礕PIO_InitStructure函数里了，这里直接调用，并且下面初始化GPIOD时，也可以直接调用)
 GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PA.8 输出高(ResetBits是输出低电平)
						 
}
 void KEY_Init(void)
{
	RCC->APB2ENR|=1<<4;     //使能PORTc时钟  
	GPIOC->CRL&=0XFFFFFFF0;		  
	GPIOC->CRL|=0X00000008; 				   
 
} 
