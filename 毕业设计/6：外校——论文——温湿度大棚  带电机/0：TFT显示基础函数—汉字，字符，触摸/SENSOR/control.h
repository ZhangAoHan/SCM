#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "delay.h"	
#include "lcd.h"
#include "w25q128.h"  
#include "text.h"	
#include "touch.h"  
#include "date.h"
#include "display.h"

extern u8 page; 

void use_touch(void);
void use_control(void);

#endif








