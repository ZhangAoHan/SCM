#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "sys.h"
#include "delay.h"	

#define LED_RED PCout(0)	
#define LED_YELLOW PCout(1)	
#define LED_GREEN PCout(2)	
#define FS PCout(3)	
#define JG PCout(4)	
#define HY PCin(7)	
	
#define PWM TIM4->CCR3
extern u8 door;
void PWM_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
void RFID_read(void);
void control(void);
void LED_Init(void);
void Rc522_date_send(void);
#endif



