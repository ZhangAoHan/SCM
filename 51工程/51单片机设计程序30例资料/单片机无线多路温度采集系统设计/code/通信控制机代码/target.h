/*****************************************************************************************
*�ļ����ƣ�target.h
*˵�������ļ�Ϊ�̵����ͷ�������������ͷ�ļ�
*���ܣ�1.�˿ڶ���
       2.������������
*�޸ģ���
*�汾��V1.0.0
*���ߣ�YuanDong
*ʱ�䣺2009.07.03
*****************************************************************************************/
#ifndef _TARGET_H_
#define _TARGET_H_ 1
#include "Include.h"
   #ifndef TARGET_GLOBAL
      #define TARGET_EXT extern
   #else
      #define TARGET_EXT
   #endif
   /*********�̵������ƶ˿ڶ���*********/
   sbit relayPort = P3^5;
   /*********���������ƶ˿ڶ���*********/
   sbit buzzerPort = P1^4;
   TARGET_EXT void relay_Init(void);
   TARGET_EXT void buzzer_Init(void);
   TARGET_EXT void relay_Command(bit status);
   TARGET_EXT void buzzer_Command(bit status);
#endif
