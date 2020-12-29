#define PWM_GLOBAL 1
#include "pwm.h"
/*****************************************************
*函数名称：pwm_init(void)
*函数功能：PWM初始化，设置定时器
*函数入口：无
*函数出口：无
*****************************************************/
void pwm_init(void)	 // 12M
{                   
	TMOD=0x20;       // 定时器1 模式2
	TL1 = 255-10;    // 1ms
	TH1 = 255-10;
	ET1 = 1;	     //定时器1边沿触发
	TR1 = 1;	     //开定时器1中断
	pwmPeriodCont =0x00;
	pwmH=0x01;
}
/*****************************************************
*函数名称：void pwm_set(const uchar NewPwmValue)
*函数功能：PWM占空比设置
*函数入口：无
*函数出口：无
*****************************************************/
void pwm_set(uchar NewPwmValue)
{
	if ((NewPwmValue >= 1)&&(NewPwmValue <= 99))   //一个周期里
	{
	  pwmH = NewPwmValue;
	}
	else										   //若占空比不在1...99范围内则输出一个尖脉冲
	{
	  pwmH =0x01;
	}									
}
/*****************************************************
*函数名称：pwmProduce(void)
*函数功能：定时器1溢出中断设置
*函数入口：无
*函数出口：无
*****************************************************/
void pwmProduce(void) interrupt 3
{
	pwmPeriodCont++;			 //PWM定时周期计数加1	   
	if(pwmPeriodCont<=pwmH)
	  PWM_OUT =1;		     // 高电平从0 到...PWM_H
	else  // 剩下的为低电平时间
	 { 
	   PWM_OUT =0;
	   if (pwmPeriodCont >= PWM_Period)// 一个频率周期结束
	   { 
		 pwmPeriodCont=0;
	   }
	 }
}