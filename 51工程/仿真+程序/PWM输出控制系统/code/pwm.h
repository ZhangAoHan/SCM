/***********************************************
*�������ܣ�����pwm,12MHZ�����£�������Ϊ100*1ms
*�汾��0.0.1
*���ߣ�lhw
*ʱ�䣺09.06.11
***********************************************/
#ifndef PWM_H
#define PWM_H
  #include "Include.h"
  #ifndef PWM_GLOBAL 
    #define PWM_EXT extern
  #else
    #define PWM_EXT
  #endif
  #define PWM_Period 100             //100%ռ�ձ�ʱ����
//*******************�˿ڶ���**********************
  sbit PWM_OUT=P1^2;	                        /*pwm����˿�ӳ��*/
//*************************************************
  PWM_EXT uchar pwmPeriodCont;	    // PWM ռ�ձȼ�����
  PWM_EXT uchar pwmH;
  PWM_EXT void  pwm_init(void);                   /*PWM��ʼ�������ö�ʱ��*/
  PWM_EXT void  pwm_set(const uchar NewPwmValue); /*PWMռ�ձ�����*/ 
#endif