#include "motor.h" 
#include "sys.h"

void Mortor_init()
{
	RCC->APB2ENR|=1<<2;        //使能GPIOA
	GPIOA->CRL&=0XFFFF0000;    
	GPIOA->CRL|=0X00003333;    // GPIOS1-C3,推挽输出、输出速度50M 
    GPIOA->ODR|=0XF;          //设置GPIOA0为输出模式
}
void Motor_PWM(u16 pwm1,u16 pwm2)          //电机驱动函数
{
	AIN1=1;
	AIN2=0;
	TIM3->CCR1 =pwm1;
	TIM3->CCR2 =pwm2;
}

