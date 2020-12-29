#include "Include.h"
#ifndef LED_H
#define LED_H  1
  #ifndef LED_GLOBAL
    #define LED_EXT extern 
  #else
    #define LED_EXT 
  #endif
  #define  LED              P0
  sbit LED_A =P0^6;
  sbit LED_B =P0^5;
  sbit LED_C =P0^4;
  sbit LED_D =P0^3;
  sbit LED_E =P0^2;
  sbit LED_F =P0^1;
  sbit LED_G =P0^0;
  sbit LED_DP=P0^7;

  sbit LED_CS1 =P2^3;                      /*数码管片选 */
  sbit LED_CS2 =P2^2;
  sbit LED_CS3 =P2^1;


  sbit LED_CS4 =P2^0;
/*----------------设定时钟在存储区中的位置 -------------------------*/	  
  #define S_L              0     //秒高位在所存储中位置 
  #define S_H              1	 //秒低位所在存储中位置 
  #define NO               3	 //抢答选手号所在缓冲位置 
  #define SET_MOD          2     //手动设定抢答时间时的模式 
/*------------------------------------------------------------------*/ 
  enum SEG_DISPLAY_MOD{DIGITAL=0x00,CHARACTER=0x01};
  /*高电平驱动 */	  
  #ifdef LED_GLOBAL
     uchar segLedCode[10]={0x7e,0x06,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};
	 /*数码管数码译码数组,led6~led0==a~g,code1~10==0~9*/
  #endif
  LED_EXT void init_led(void);
  LED_EXT void ledWrite(uchar c,uchar n,uchar mod);
  /*循环显示子函数，segCode为要显示的数据组，segCodeMode为要相应数据的显示模式 */
  LED_EXT void ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber);	

#endif