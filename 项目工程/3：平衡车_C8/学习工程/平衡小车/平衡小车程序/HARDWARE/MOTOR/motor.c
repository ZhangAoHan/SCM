#include "motor.h" 
#include "sys.h"

void Mortor_init()
{
	RCC->APB2ENR|=1<<2;        //使能GPIOA
	GPIOA->CRH&=0X0000FFFF;    
	GPIOA->CRH|=0X33330000;    // GPIOS1-C3,推挽输出、输出速度50M 
    GPIOA->ODR|=1<<12;          //设置GPIOA0为输出模式
	GPIOA->ODR|=1<<13;
	GPIOA->ODR|=1<<14;
	GPIOA->ODR|=1<<15;
	AIN1=0;   //初始停转
	AIN2=0;
	BIN1=0;
	BIN2=0;
}
void Motor_PWM(u16 pwm1,u16 pwm2)          //电机驱动函数
{
	AIN1=0;
	AIN2=1;
	BIN1=0;
	BIN2=1;
	TIM1_oc1_pwm =pwm1;
	TIM1_oc2_pwm =pwm2;
}

