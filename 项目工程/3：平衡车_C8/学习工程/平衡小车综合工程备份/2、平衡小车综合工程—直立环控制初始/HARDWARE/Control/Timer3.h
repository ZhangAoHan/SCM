#ifndef __TIMER3_H
#define __TIMER3_H
#include "sys.h"
void TIME3_init(void);
void Motor_Back(void);
void Motor_Go(void);
void Motor_Control(void);
extern float Angle_Balance;
extern float Gyro_Balance;
extern float Pitch;
extern float Roll;
extern short gyro[3];
#endif



