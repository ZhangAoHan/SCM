#ifndef INCLUDE_H
#define INCLUDE_H
  #include "AT89X51.h"
  #include "intrins.h"
  #define uchar unsigned  char
  #define uint  unsigned  int

  #define _BV(x)         (1<<(x))
  #define GET_BIT(x,y)   (((x)&(1<<(y)))==0?0:1)               //取x变量y位的数据 
  #define SET_BIT(x,y)   ((x)|=(0x0001<<(y)))	               //置位x变量y位
  #define CLR_BIT(x,y)   ((x)&=~(0x0001<<(y)))                 //清零x变量y位
  #define LET_BIT(x,y,z) ((x)=(x)&(~(0x0001<<(y)))|(z)<<(y))   //置位或清零x变量y位

  #define F_CPU    11059200UL                                  //cpu震荡周期 
  #define sei()    (EA=1)	                                   //开总中断 
  #define cli()    (EA=0)	                                   //关总中断 

#endif