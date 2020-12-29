#ifndef DOOR_BELL_H
#define DOOR_BELL_H 1
   #include "AT89X51.h"
   #include "intrins.h"
   #define uchar unsigned char
   #define uint  unsigned int
   #define sei() (EA=1)
   #define cli() (EA=0)
   #define BELL_OUT  P1_7
   void timer0_init(void); //定时器0初始化
   void int0_init(void);   //外部中断0初始化,实现门铃按键的检测
#endif