#ifndef TARGET_H
#define TARGET_H
#include "Include.h"
#ifndef TARGET_GLOBAL
  #define TARGET_EXT extern
#else
  #define TARGET_EXT
#endif
TARGET_EXT void usart0_initial(void);           //ʹ��timer1,���ʼ����usart0��ʼ����
TARGET_EXT void send_char(uchar txd);           //���ڷ���һ���ַ�
TARGET_EXT void send_str(uchar *str,uchar len); //���ڷ���һ���ַ���  
#endif