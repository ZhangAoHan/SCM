#ifndef TARGET_H
#define TARGET_H 1
  #include "Include.h"
  #ifndef TARGET_GLOAL 
    #define TARGET_EXT extern
  #else
    #define TARGET_EXT
  #endif
  TARGET_EXT void usart0_init(void);              //ʹ��timer1,���ʼ����usart0��ʼ����
  TARGET_EXT void send_char(uchar txd);           //���ڷ���һ���ַ�
  TARGET_EXT void send_str(uchar *str,uchar len); //���ڷ���һ���ַ��� 
  TARGET_EXT uchar get_char(void);                //���ڽ���һ���ַ�
#endif