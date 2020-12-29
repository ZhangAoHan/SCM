/***********************************************
*驱动功能：产生pwm,12MHZ晶振下，总周期为100*1ms
*版本：0.0.1
*作者：lhw
*时间：09.06.11
***********************************************/
#ifndef PWM_H
#define PWM_H
  #include "Include.h"
  #ifndef PWM_GLOBAL 
    #define PWM_EXT extern
  #else
    #define PWM_EXT
  #endif
  #define PWM_Period 100             //100%占空比时标数
//*******************端口定义**********************
  sbit PWM_OUT=P1^2;	                        /*pwm输出端口映射*/
//*************************************************
  PWM_EXT uchar pwmPeriodCont;	    // PWM 占空比计数器
  PWM_EXT uchar pwmH;
  PWM_EXT void  pwm_init(void);                   /*PWM初始化，设置定时器*/
  PWM_EXT void  pwm_set(const uchar NewPwmValue); /*PWM占空比设置*/ 
#endif