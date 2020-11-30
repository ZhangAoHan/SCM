#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H
#include <sys.h>	 

u8 motor_init(void);
void motor_stop(void);
void motor_down(void);
void motor_up(void);
	void use_motor_control(u8 lc) ;
	void use_touch_scan(void);


#endif


