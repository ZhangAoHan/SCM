#ifndef __CONTROL_H
#define __CONTROL_H 
#include "sys.h"   
#include "delay.h"	
#include "24l01.h"
#include "lcd.h"  
#include "touch.h"  

//LED¶Ë¿Ú¶¨Òå
#define LED_RED PCout(0)	
#define LED_BLUE PCout(1)	
#define LED_GREEN PCout(2)	

extern u8 tmp_buf[33];


void Nrf_communicate(void);
void user_control(void);	

void date_display(u8 y);
void DL_display(void)  ;
void page_1(void)  ;
void page_2(void)      ;
void use_touch(void);
void LED_Init(void);
#endif

