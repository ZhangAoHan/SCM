#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#define KEY_UP  PAin(12)   	//PC5

void Nrf_communicate(void);
void use_control(void);
void Rc522_read(void); 
void display(void);
void Key_init(void);
void id_scan(void);
void old_id_read(void);
#endif



