#ifndef __LED_H
#define __LED_H
#include "sys.h"
#define led1 PAout(1)
#define led2 PAout(3)
#define led0 PCout(15)
#define beep PCout(13)
void led_init(void);
#endif


