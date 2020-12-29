#include "Include.h"
#ifndef LED_H
#define LED_H  1
  #ifndef LED_GLOBAL
    #define LED_EXT extern 
  #else
    #define LED_EXT 
  #endif
  #define  LED              P0
  #define  LED_CS           P3
  #define  WARN_TRUMPET     P1_7  //定义报警喇叭所在端口 

  sbit LED_A = P0^6;
  sbit LED_B = P0^5;
  sbit LED_C = P0^4;
  sbit LED_D = P0^3;
  sbit LED_E = P0^2;
  sbit LED_F = P0^1;
  sbit LED_G = P0^0;
  sbit LED_DP = P0^7;

  sbit LED_CS1 = P3^7;            //数码管片选 
  sbit LED_CS2 = P3^6;
  sbit LED_CS3 = P3^5;
  sbit LED_CS4 = P3^4;
  sbit LED_CS5 = P3^3;
  sbit LED_CS6 = P3^2;
  sbit LED_CS7 = P3^1;
  sbit LED_CS8 = P3^0;

  /*----------------设定时钟在存储区中的位置 -------------------------*/	  
  #define S_L              0     //秒高位在所存储中位置 
  #define S_H              1	 //秒低位所在存储中位置 
  #define M_L              3     //分低位所在存储中位置 
  #define M_H              4	 //分高位所在存储中位置 
  #define H_L	           6	 //时低位所在存储中位置 
  #define H_H              7 	 //时高位所在存储中位置 
  #define DIGIAL_MOD_ONE   2	 //模式字符1所在存储位置  
  #define DIGIAL_MOD_TWO   5	 //模式字符2所在存储位置   

  #define LED_MODE_COUNT   0x01	 //显示当前时钟 
  #define LED_MODE_ALARM   0x48  //显示闹钟时间 
  /*------------------------------------------------------------------*/ 
  enum SEG_DISPLAY_MOD{DIGITAL = 0x00,CHARACTER = 0x01};
      //高电平驱动 	  
  #ifdef LED_GLOBAL
     uchar segLedCode[10] = {0x7e,0x06,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};
	 //数码管数码译码数组,led6~led0==a~g,code1~10==0~9
  #endif
  LED_EXT void init_led(void);
  LED_EXT void ledWrite(uchar c,uchar n,uchar mod);
  /*循环显示子函数，segCode为要显示的数据组，segCodeMode为要相应数据的显示模式*/ 
  LED_EXT void ledSweepDisplay(uchar *segCode,uchar segCodeMod);	

#endif