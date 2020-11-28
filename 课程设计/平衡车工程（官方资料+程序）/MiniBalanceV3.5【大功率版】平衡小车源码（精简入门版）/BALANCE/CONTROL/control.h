#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265
#define ZHONGZHI 1
extern	int Balance_Pwm,Velocity_Pwm;
int EXTI15_10_IRQHandler(void);
int balance(float angle,float gyro);
int velocity(int encoder_left,int encoder_right);
void Set_Pwm(int moto1,int moto2);
void Xianfu_Pwm(void);
u8 Turn_Off(float angle);
void Get_Angle(void);
int myabs(int a);
#endif
