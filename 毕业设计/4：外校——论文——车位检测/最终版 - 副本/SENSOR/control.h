#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "delay.h"	
extern u8 use1,use2,use3; 
extern u16 t1,t2,t3; 
extern u8 door;
void LCD_init_display(void);
void LCD_page0_display(void);   //主页面设计;
void temp(void);
void RFID_display(void);
void RFID_read(void);
void control(void);
void user_date_display(void);
void use_touch(void);
#endif

