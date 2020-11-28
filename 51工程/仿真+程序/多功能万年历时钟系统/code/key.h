#ifndef KEY_H
#define KEY_H
  #include "Include.h"
  #ifndef KEY_GLOBAL
    #define KEY_EXT extern
  #else
    #define KEY_EXT
  #endif
  #define READ_KEY(x,name,b)       ((x)?(b|=name):(b&=~name) )
//---------------------���̶˿ڶ���-------------------------------------
  #define  IN_PRESS_UP  	    P0_0    //�������Ӽ��˿�ӳ��
  #define  IN_PRESS_DOWN		P0_1	//���ݼ��ټ��˿�ӳ��
  #define  IN_PRESS_CLEAR	    P0_2	//��ռ��˿�ӳ��
  #define  IN_PRESS_FUNC		P0_3	//�˵����˿�ӳ��
//----------------------��ֵӳ��-----------------------------------------
  #define  KEY_FORCE_VALUE  0	 //������Ч��ֵ
  enum KEY_VALUE{KEY_UP=0x01,KEY_DOWN=0x02,KEY_CLEAR=0x04,KEY_FUNC=0x08,KEY_NULL=0x00};
  KEY_EXT void key_delay_us(uint us);
  KEY_EXT void key_init(void);
  KEY_EXT void Key_Idle(void);
  KEY_EXT uchar Key_Scan(void);
  KEY_EXT void Key_Set_Clock(uchar * clock_time);
  KEY_EXT void Key_Set_Alarm(uchar * alarm_time);
  KEY_EXT void Key_Function(uchar * clock_time,uchar* alarm_time);
#endif