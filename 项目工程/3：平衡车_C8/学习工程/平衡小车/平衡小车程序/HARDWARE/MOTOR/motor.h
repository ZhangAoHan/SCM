#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define AIN2   PAout(15)    //右 负（正转）
#define AIN1   PAout(14)    //右 正（正转）
#define BIN1   PAout(13)    //左 正（正转）
#define BIN2   PAout(12)    //左 负（正转）
void Mortor_init(void);
void Motor_PWM(u16 pwm1,u16 pwm2) ;
#endif

