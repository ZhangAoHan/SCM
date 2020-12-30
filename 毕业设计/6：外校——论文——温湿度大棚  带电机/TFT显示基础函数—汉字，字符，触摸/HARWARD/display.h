#ifndef __DISPLAY_H
#define __DISPLAY_H	
#include "sys.h"
							  
void LCD_Init_Display(void);
void Use1_init_diaplsy(void);
void Use1_date_display(void);
void date_save(void);
void date_init_display(u8 ch)    ;
void date_display(u8 ch);
void Block_date_display(void)      ;
void Block_init_display(void)    ;
#endif 
