#include "led.h"
#include "sys.h"
void led_init(void)
{
	RCC->APB2ENR|=1<<2;  //使能GPIOA时钟
	RCC->APB2ENR|=1<<4;  //使能GPIOC时钟
	GPIOA->CRL&=0xffff0f0f;    
	GPIOA->CRL|=0x00003030;    //设置GPIOA1 3：推挽输出，输出速度为50M
	GPIOA->ODR|=0x0006;    //将GPIOA1和GPIOA3初始输出为高（灭）
	GPIOC->CRH&=0x0f0fffff;    
	GPIOC->CRH|=0x30300000;    //设置GPIOC15：推挽输出，输出速度为50M
	GPIOC->ODR|=0xa000;    //将GPIOC15初始输出为高（灭）
}

