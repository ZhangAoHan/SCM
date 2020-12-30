#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "sys.h"
#include "delay.h"	
#include "lcd.h"
#include "w25q128.h"  
#include "text.h"	
#include "adc_dht11.h"
#include "date.h"

extern u8 temperature;  	    
extern u8 humidity;
extern u16 adcx;	

void init_display(void);
void main_display(void)  ;
void use_1_init_display(void) ;
void use_1_data_display(void)  ;

#endif







