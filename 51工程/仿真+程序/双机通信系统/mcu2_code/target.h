#ifndef TARGET_H
#define TARGET_H
#include "Include.h"
#ifndef TARGET_GLOBAL
  #define TARGET_EXT extern
#else
  #define TARGET_EXT
#endif
TARGET_EXT void usart0_initial(void);           //使用timer1,其初始化在usart0初始化中
TARGET_EXT void send_char(uchar txd);           //串口发送一个字符
TARGET_EXT void send_str(uchar *str,uchar len); //串口发送一行字符串  
#endif