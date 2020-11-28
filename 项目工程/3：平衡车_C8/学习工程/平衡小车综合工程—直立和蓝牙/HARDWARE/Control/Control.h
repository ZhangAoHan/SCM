#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "Motor.h"
extern float  Angle_Balance, Gyro_Balance;
extern int Moto1,Moto2; 
extern int left,right;
extern int 	Motor;
int balance(float angle,float gyro);
void Set_Pwm(int moto1,int moto2);
void Xianfu_Pwm(void);
int myabs(int a);
int velocity(int Left,int Right,int motor);
void Motor_Control(void);
u8 Turn_Off(float angle);
#endif




