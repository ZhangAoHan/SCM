#ifndef TARGET_H
#define TARGET_H 1
  #include "lcd.h"
  #ifndef TARGET_GLOBAL
    #define TARGET_EXT extern
  #else
    #define TARGET_EXT
  #endif
  sbit MOTER_M1=P2^0;
  sbit MOTER_M2=P2^1;
  sbit MOTER_M3=P2^2;
  sbit MOTER_M4=P2^3;
  /**********�������״̬*****************/
  //ֹͣ,��ת����,��ת����,��ת����
  enum MOTER_STATE_ONE{MOTER_STOP=0x01,MOTER_FRONT_ADD=0x02,MOTER_FRONT_REDUCE=0x03,MOTER_FRONT_NORMAL=0x04};
  //��ת����,��ת����,��ת����,��ת����,��ת����
  enum MOTER_STATE_TWO{MOTER_FRONT_LOWER=0x05,MOTER_QUEEN_ADD=0x06,MOTER_QUEEN_REDUCE=0x07,MOTER_QUEEN_NOMAL=0x08,MOTER_QUEEN_LOWER=0x09};
  TARGET_EXT void timer0_init(void);
  TARGET_EXT void target_init(void);
  TARGET_EXT void moter_state_display(uchar moterState); //���״̬��ʾ 
  TARGET_EXT void ground(step);	   //�������ת��,step�ְ˲� 
#endif