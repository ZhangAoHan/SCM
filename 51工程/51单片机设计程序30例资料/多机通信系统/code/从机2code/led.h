/*********************************************************
*�������ƣ��߶�LED���������
*���ܣ������ڴ�������74LS373��7���������ʾ
*�汾��V0.0.0
*���ߣ�yd
*ʱ�䣺09.06.09
*********************************************************/
#ifndef LED_H
#define LED_H 1
#include"Include.h"
  #ifndef LED_GLOBAL
    #define LED_EXT extern
  #else
    #define LED_EXT
  #endif
  #define  LED            P0     //����LED���ݶ˿�
  #define  LED_CS1        P2_1   //74LS373������Ƭѡ�˿�
  #define  CS_FORCE_VALUE 1      //74LS373Ƭѡ��Ч��ƽ
  enum SEG_DISPLAY_MOD{DIGITAL=0x00,CHARACTER=0x01};  //��������ģʽ�����ֻ������ֶ���ʾ
  //�ߵ�ƽ����	  
  #ifdef LED_GLOBAL
     uchar segLedCode[10]={0x7e,0x06,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};
	 //�����������������,led6~led0==a~g,code1~10==0~9
  #endif
  LED_EXT void led_init(void);	                    //����ܳ�ʼ��
  LED_EXT void ledWrite(uchar c,uchar n,uchar mod); //���n�������дmodģʽ������c
  LED_EXT void delay_us(uint us);                   //����΢�뼶��ʱ����   	
#endif