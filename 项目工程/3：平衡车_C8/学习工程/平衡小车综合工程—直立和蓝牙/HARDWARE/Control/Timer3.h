#ifndef __TIMER3_H
#define __TIMER3_H
#include "sys.h"
#include "Motor.h" 

void TIME3_init(void);
//void Motor_Control(void);
void Bluetooth(void);

extern float Angle_Balance;
extern float Gyro_Balance;
extern float Pitch;
extern float Roll;
extern short gyro[3];
extern int left,right;
#endif



