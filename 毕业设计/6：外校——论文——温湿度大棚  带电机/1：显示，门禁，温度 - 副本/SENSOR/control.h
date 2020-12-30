#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "delay.h"	
extern u8 tempdate1,date1,tempdate2,date2,tempdate3,date3,tempdate4,date4,tempdate5,date5;
extern u8 tempoutdate1,outdate1,tempoutdate2,outdate2,tempoutdate3,outdate3,tempoutdate4,outdate4,tempoutdate5,outdate5;
extern u8 tim;  
extern u8 t;  
void init_display(void) ;
void main_display(void) ;
void date_read(void);
void use_touch(void);
void control(void);
void RFID_read(void);
#endif

