#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define AIN2   PAout(0)
#define AIN1   PAout(1)    //µç»úÏß
#define BIN1   PAout(2)
#define BIN2   PAout(3)
void Mortor_init(void);
void Motor_PWM(u16 pwm1,u16 pwm2) ;
#endif

