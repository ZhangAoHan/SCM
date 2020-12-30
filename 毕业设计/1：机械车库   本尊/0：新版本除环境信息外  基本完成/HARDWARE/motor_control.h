#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H
#include "sys.h"



void motor_up(void);
void motor_down(void);
void motor_stop(void);
u8 motor_rest(void);           //µçÌÝ¸´Î»
void use_touch_scan(void) ;
void use_motor_control(u8 lc)     ;
void cl_display(u8 lc,u8 s) ;
#endif


