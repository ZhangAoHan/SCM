#ifndef INCLUDE_H
#define INCLUDE_H  1
  #include "AT89X51.h"
  #include "intrins.h"
  #define uchar unsigned  char
  #define uint  unsigned  int
  #define GET_BIT(x,y) (((x)&(1<<(y)))==0?0:1)
  #define SET_BIT(x,y) ((x)|=(0x0001<<(y)))
  #define CLR_BIT(x,y) ((x)&=~(0x0001<<(y)))
  #define SET_BIT(x,y) ((x)|=(0x0001<<(y)))
  #define CLR_BIT(x,y) ((x)&=~(0x0001<<(y)))  
  #define _BV(x)       (1<<(x))
#endif