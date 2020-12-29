/*********************************************************
*驱动名称：七段LED数码管驱动
*功能：适用于带锁存器74LS373的7段数码管显示
*版本：V0.0.0
*作者：yd
*时间：09.06.09
*********************************************************/
#ifndef LED_H
#define LED_H 1
#include"Include.h"
  #ifndef LED_GLOBAL
    #define LED_EXT extern
  #else
    #define LED_EXT
  #endif
  #define  LED            P0     //定义LED数据端口
  #define  LED_CS1        P2_1   //74LS373锁存器片选端口
  #define  CS_FORCE_VALUE 1      //74LS373片选有效电平
  enum SEG_DISPLAY_MOD{DIGITAL=0x00,CHARACTER=0x01};  //数码管输出模式，数字或任意字段显示
  //高电平驱动	  
  #ifdef LED_GLOBAL
     uchar segLedCode[10]={0x7e,0x06,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};
	 //数码管数码译码数组,led6~led0==a~g,code1~10==0~9
  #endif
  LED_EXT void led_init(void);	                    //数码管初始化
  LED_EXT void ledWrite(uchar c,uchar n,uchar mod); //向第n个数码管写mod模式的内容c
  LED_EXT void delay_us(uint us);                   //声明微秒级延时函数   	
#endif