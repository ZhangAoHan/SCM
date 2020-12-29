/*********************************************************
*驱动名称：七段LED数码管驱动
*功能：适用于带1个锁存器74LS373的7段数码管显示
*修改：修改驱动使其适用于三个数码管显示
*版本：V0.0.1
*作者：kxm
*时间：09.06.11
*********************************************************/
#ifndef LED_H
#define LED_H 1
#include"Include.h"
  #ifndef LED_GLOBAL
    #define LED_EXT extern
  #else
    #define LED_EXT
  #endif
  #define  CS_FORCE_VALUE 1      /*74LS373片选有效电平*/
//***************数码管端口定义****************************
  #define  LED            P0     /*定义LED数据端口*/
  #define  LED_CS1        P2_0   /*74LS373锁存器1片选端口*/
  #define  LED_CS2		  P2_1	 /*74LS373锁存器2片选端口*/
  #define  LED_CS3        P2_2	 /*74LS373锁存器3片选端口*/
//*********************************************************
  enum SEG_DISPLAY_MOD{DIGITAL=0x00,CHARACTER=0x01};  /*数码管输出模式，数字或任意字段显示*/
  /*高电平驱动 */	  
  #ifdef LED_GLOBAL
     uchar segLedCode[10]={0x7e,0x30,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};
	 /*数码管数码译码数组,led6~led0==a~g,code1~10==0~9*/
  #endif
  LED_EXT void led_init(void);	                    /*数码管初始化*/
  LED_EXT void ledWrite(uchar c,uchar n,uchar mod); /*向第n个数码管写mod模式的内容c*/  	
#endif