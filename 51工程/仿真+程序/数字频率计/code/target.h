#ifndef TARGET_H
#define TARGET_H 1
  #include "Include.h"
  #ifndef TARGET_GLOBAL
    #define TARGET_EXT extern
  #else 
    #define TARGET_EXT
  #endif
  TARGET_EXT void timer0_init(void);    //timer0��ʼ��,MODEL1,timer 
  TARGET_EXT void int0_init(void);      //�ⲿ�ж�0��ʼ�� 
  TARGET_EXT void target_init(void);  
  TARGET_EXT uint get_fre_number(void);	//��ȡƵ���Ӻ��� 
#endif