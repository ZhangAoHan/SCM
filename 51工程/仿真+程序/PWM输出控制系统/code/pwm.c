#define PWM_GLOBAL 1
#include "pwm.h"
/*****************************************************
*�������ƣ�pwm_init(void)
*�������ܣ�PWM��ʼ�������ö�ʱ��
*������ڣ���
*�������ڣ���
*****************************************************/
void pwm_init(void)	 // 12M
{                   
	TMOD=0x20;       // ��ʱ��1 ģʽ2
	TL1 = 255-10;    // 1ms
	TH1 = 255-10;
	ET1 = 1;	     //��ʱ��1���ش���
	TR1 = 1;	     //����ʱ��1�ж�
	pwmPeriodCont =0x00;
	pwmH=0x01;
}
/*****************************************************
*�������ƣ�void pwm_set(const uchar NewPwmValue)
*�������ܣ�PWMռ�ձ�����
*������ڣ���
*�������ڣ���
*****************************************************/
void pwm_set(uchar NewPwmValue)
{
	if ((NewPwmValue >= 1)&&(NewPwmValue <= 99))   //һ��������
	{
	  pwmH = NewPwmValue;
	}
	else										   //��ռ�ձȲ���1...99��Χ�������һ��������
	{
	  pwmH =0x01;
	}									
}
/*****************************************************
*�������ƣ�pwmProduce(void)
*�������ܣ���ʱ��1����ж�����
*������ڣ���
*�������ڣ���
*****************************************************/
void pwmProduce(void) interrupt 3
{
	pwmPeriodCont++;			 //PWM��ʱ���ڼ�����1	   
	if(pwmPeriodCont<=pwmH)
	  PWM_OUT =1;		     // �ߵ�ƽ��0 ��...PWM_H
	else  // ʣ�µ�Ϊ�͵�ƽʱ��
	 { 
	   PWM_OUT =0;
	   if (pwmPeriodCont >= PWM_Period)// һ��Ƶ�����ڽ���
	   { 
		 pwmPeriodCont=0;
	   }
	 }
}