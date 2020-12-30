#ifndef __IO_CONTROL_H
#define __IO_CONTROL_H
#include <sys.h>	 

#define KEY_START  PAin(15)   	//PC5
#define KEY_UP  PAin(12)   	//PC5
#define KEY_DOWN  PAin(11)	 	//PA15 
#define LED_RED PBout(0)	// PD2	
#define LED_GREEN PBout(1)	// PD2	



void Io_init(void);
#endif



