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
  #define  WARN_TRUMPET     P1_7  //���屨���������ڶ˿� 

  sbit LED_A = P0^6;
  sbit LED_B = P0^5;
  sbit LED_C = P0^4;
  sbit LED_D = P0^3;
  sbit LED_E = P0^2;
  sbit LED_F = P0^1;
  sbit LED_G = P0^0;
  sbit LED_DP = P0^7;

  sbit LED_CS1 = P3^7;            //�����Ƭѡ 
  sbit LED_CS2 = P3^6;
  sbit LED_CS3 = P3^5;
  sbit LED_CS4 = P3^4;
  sbit LED_CS5 = P3^3;
  sbit LED_CS6 = P3^2;
  sbit LED_CS7 = P3^1;
  sbit LED_CS8 = P3^0;

  /*----------------�趨ʱ���ڴ洢���е�λ�� -------------------------*/	  
  #define S_L              0     //���λ�����洢��λ�� 
  #define S_H              1	 //���λ���ڴ洢��λ�� 
  #define M_L              3     //�ֵ�λ���ڴ洢��λ�� 
  #define M_H              4	 //�ָ�λ���ڴ洢��λ�� 
  #define H_L	           6	 //ʱ��λ���ڴ洢��λ�� 
  #define H_H              7 	 //ʱ��λ���ڴ洢��λ�� 
  #define DIGIAL_MOD_ONE   2	 //ģʽ�ַ�1���ڴ洢λ��  
  #define DIGIAL_MOD_TWO   5	 //ģʽ�ַ�2���ڴ洢λ��   

  #define LED_MODE_COUNT   0x01	 //��ʾ��ǰʱ�� 
  #define LED_MODE_ALARM   0x48  //��ʾ����ʱ�� 
  /*------------------------------------------------------------------*/ 
  enum SEG_DISPLAY_MOD{DIGITAL = 0x00,CHARACTER = 0x01};
      //�ߵ�ƽ���� 	  
  #ifdef LED_GLOBAL
     uchar segLedCode[10] = {0x7e,0x06,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};
	 //�����������������,led6~led0==a~g,code1~10==0~9
  #endif
  LED_EXT void init_led(void);
  LED_EXT void ledWrite(uchar c,uchar n,uchar mod);
  /*ѭ����ʾ�Ӻ�����segCodeΪҪ��ʾ�������飬segCodeModeΪҪ��Ӧ���ݵ���ʾģʽ*/ 
  LED_EXT void ledSweepDisplay(uchar *segCode,uchar segCodeMod);	

#endif