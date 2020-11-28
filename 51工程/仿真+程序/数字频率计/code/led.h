/***************************************************
*驱动名称：七段LED数码管驱动
*驱动功能：实现四位共阴极七段LED数码管的循环显示
*作者：yd
*时间：09.06.20
****************************************************/
#include "Include.h"
#ifndef LED_H
#define LED_H  1
  #ifndef LED_GLOBAL
    #define LED_EXT extern 
  #else
    #define LED_EXT 
  #endif
  #define  LED              P0	        //数码管数据端口配置
  sbit LED_CS1 =P2^0;                   //数码管片选端口配置 
  sbit LED_CS2 =P2^1;
  sbit LED_CS3 =P2^2;
  sbit LED_CS4 =P2^3;
  enum SEG_DISPLAY_MOD{DIGITAL=0x00,CHARACTER=0x01};
  //共阴极显示方式	  
  #ifdef LED_GLOBAL
     uchar segLedCode[10]={0x7e,0x06,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};
	 //数码管数码译码数组,led6~led0==a~g,code1~10==0~9
  #endif
  LED_EXT void init_led(void);
  LED_EXT void ledWrite(uchar c,uchar n,uchar mod);
  //循环显示子函数，segCode为要显示的数据组，segCodeMode为要相应数据的显示模式
  LED_EXT void ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber);	

#endif