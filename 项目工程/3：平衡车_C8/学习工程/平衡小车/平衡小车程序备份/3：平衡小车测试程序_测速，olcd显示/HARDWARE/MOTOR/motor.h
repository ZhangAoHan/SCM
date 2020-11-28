#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define AIN2   PAout(15)
#define AIN1   PAout(14)    //µç»úÏß
#define BIN1   PAout(13)
#define BIN2   PAout(12)
void Mortor_init(void);
void Motor_PWM(u16 pwm1,u16 pwm2) ;
#endif

