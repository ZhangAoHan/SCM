#ifndef DOOR_BELL_H
#define DOOR_BELL_H 1
   #include "AT89X51.h"
   #include "intrins.h"
   #define uchar unsigned char
   #define uint  unsigned int
   #define sei() (EA=1)
   #define cli() (EA=0)
   #define BELL_OUT  P1_7
   void timer0_init(void); //��ʱ��0��ʼ��
   void int0_init(void);   //�ⲿ�ж�0��ʼ��,ʵ�����尴���ļ��
#endif