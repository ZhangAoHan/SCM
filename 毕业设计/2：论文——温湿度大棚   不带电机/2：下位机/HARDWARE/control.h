#ifndef __CONTROL_H
#define __CONTROL_H 
#include "sys.h"   
#include "delay.h"	
#include "24l01.h"
#include "dht11.h"
#include "adc.h"

extern u8 tmp_buf[33];


void Nrf_communicate(void);
void user_control(void);	
void date_read(void);
void Rc522_read(void);
#endif

