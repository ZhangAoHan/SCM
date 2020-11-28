#ifndef  LED_H
#define  LED_H  1
  #include "Include.h"
  #ifndef LED_GLOBAL
    #define LED_EXT extern
  #else 
    #define LED_EXT
  #endif
//-------------------------数码管端口定义-------------------------------
  #define LED P0        //数码管数据端口
// sbit LED_A =P0^6; sbit LED_B =P0^5;sbit LED_C =P0^4;sbit LED_D =P0^3;
// sbit LED_E =P0^2; sbit LED_F =P0^1;sbit LED_G =P0^0;sbit LED_DP=P0^7;
  sbit LED_CS1 =P2^0;   //数码管片选信号端口
  sbit LED_CS2 =P2^1;
  sbit LED_CS3 =P2^2;
  sbit LED_CS4 =P2^3;
  sbit LED_CS5 =P2^4;
  sbit LED_CS6 =P2^5;
  sbit LED_CS7 =P2^6;
  sbit LED_CS8 =P2^7;
//-------------------------------------------------------------------------
  LED_EXT code uchar ledCode[10];   //数码管译码数组,led6~led0==a~g,code0~9==0~9
  LED_EXT void led_init(void);                    //数码管显示初始化
  LED_EXT void ledWrite(uchar c,uchar n);        //向第n个数码管写数据c
  LED_EXT void ledSweepDisplay(uchar *segCode,uchar ledLen);  //ledLen个数码管循环显示
  LED_EXT void ledDelay(uint us);	             //毫秒级延时函数
#endif