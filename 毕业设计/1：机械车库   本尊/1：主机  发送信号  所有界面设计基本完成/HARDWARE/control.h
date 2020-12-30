#ifndef __CONTROL_H
#define __CONTROL_H
#include <sys.h>	 

void use_control(void);
void DL_Display(void)   ;
void Error_0_display(void)  ;
void Nrf_communicate(void)   ;
void display_main(void)    ;
void use_motor_control(u8 mode);
void motor_up(void);
void motor_down(void);
void motor_stop(void);
void use_touch_scan(void);
void use_motor_control(u8 lc)  ;
u8 motor_rest(void) ;
void save_car_display(void);
void qu_car_display(void);
void Error_1_display(void) ;
#endif
