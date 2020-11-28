#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "Motor.h" 

void TIME3_init(void);
void Motor_Control(void);
void Bluetooth(void);
int Read_Encoder(u8 TIMX);

extern float Angle_Balance;
extern float Gyro_Balance;
extern float Roll;
extern short gyro[3];
extern int left,right;
#endif



