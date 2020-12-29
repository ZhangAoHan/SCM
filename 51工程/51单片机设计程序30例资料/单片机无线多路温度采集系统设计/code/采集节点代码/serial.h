/*****************************************************************************************
*�ļ����ƣ�serial.h
*˵�������ļ�Ϊ����ͨ����������ͷ�ļ�
*���ܣ�1.�˿ڶ���
       2.������������
*�޸ģ���
*�汾��V1.0.0
*���ߣ�YuanDong
*ʱ�䣺2009.07.03
*****************************************************************************************/
#ifndef  _SERIAL_H_
#define  _SERIAL_H_ 1
#include "Include.h"
   #ifndef  SERIAL_GLOBAL
     #define SERIAL_EXT extern 
   #else
     #define SERIAL_EXT
   #endif   
   SERIAL_EXT void  serial_Init(void);                   //���ڳ�ʼ��
   SERIAL_EXT void  serial_PutChar(uchar sendChar);      //���ڷ���һ���ַ�
   SERIAL_EXT void  serial_PutStr(uchar *str,uchar len); //���ڷ���һ���ַ���
   SERIAL_EXT uchar serial_GetChar(void);                //���ڽ���һ���ַ�
#endif
