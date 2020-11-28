#include "motor.h" 
#include "sys.h"

void Mortor_init()
{
	RCC->APB2ENR|=1<<2;        //ʹ��GPIOA
	GPIOA->CRL&=0XFFFF0000;    
	GPIOA->CRL|=0X00003333;    // GPIOS1-C3,�������������ٶ�50M 
    GPIOA->ODR|=0XF;          //����GPIOA0Ϊ���ģʽ
}
void Motor_PWM(u16 pwm1,u16 pwm2)          //�����������
{
	AIN1=1;
	AIN2=0;
	TIM3->CCR1 =pwm1;
	TIM3->CCR2 =pwm2;
}

