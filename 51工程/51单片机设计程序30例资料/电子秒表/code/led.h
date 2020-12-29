/**********************************************************
*�������ƣ��߶�LED���������
*�������ܣ�ʵ��6λ�������߶�LED����ܵ�ѭ����ʾ
*����:yd
*ʱ�䣺09.06.20
**********************************************************/
#include "Include.h"
#ifndef LED_H
#define LED_H  1
  #ifndef LED_GLOBAL
    #define LED_EXT extern 
  #else
    #define LED_EXT 
  #endif
  #define  LED              P0			   //��������ݶ˿�ӳ��
  sbit LED_CS1 =P2^0;                      //�����Ƭѡ
  sbit LED_CS2 =P2^1;
  sbit LED_CS3 =P2^2;
  sbit LED_CS4 =P2^3;
  sbit LED_CS5 =P2^4;
  sbit LED_CS6 =P2^5;
  sbit LED_CS7 =P2^6;
  sbit LED_CS8 =P2^7;
  enum SEG_DISPLAY_MOD{DIGITAL=0x00,CHARACTER=0x01}; //�����ѭ����ʾʱ��Ҫ��ʾ���ݵ�����	  
  #ifdef LED_GLOBAL	 //��������ʾ
     uchar segLedCode[10]={0x7e,0x06,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};
	 /*�����������������,led6~led0==a~g,code1~10==0~9*/
  #endif
  LED_EXT void led_init(void);  					//����ܳ�ʼ��
  LED_EXT void ledWrite(uchar c,uchar n,uchar mod);	//һ��дһλ�����
  //ѭ����ʾ�Ӻ�����segCodeΪҪ��ʾ�������飬segCodeModeΪҪ��Ӧ���ݵ���ʾģʽ
  LED_EXT void ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber);	

#endif