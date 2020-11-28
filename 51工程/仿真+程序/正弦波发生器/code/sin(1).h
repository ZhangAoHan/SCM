/****************************************************
*�ļ����ƣ�sin.h
*�ļ����ܣ�����DAC0832�������Ҳ�
*�汾��0.0.1
*���ߣ�yd
*ʱ�䣺09.05.13
*****************************************************/
#ifndef SIN_H
#define SIN_H 1
  #include "Include.h"
  #ifndef SIN_GLOBAL
    #define SIN_EXT extern
  #else 
    #define SIN_EXT
  #endif
  SIN_EXT code uchar Sin[128];
//----------DAC0832���ݶ˿�ӳ��------------
  #define  DAC0832       P1 
//------------------------------------------
  #define  SIN_FRE       100UL     //���Ҳ�Ƶ�� HZ
  #define  SIN_SEG       64UL      //���Ҳ���������
  #define  SIN_SPACING   2         //�������Ҳ�ʱ��SIn������ȡ������
//---------------------------------------------
  SIN_EXT uchar timer0TH0;      //��ʱ��0 TH0����ֵ�Ĵ����
  SIN_EXT uchar timer0TL0;      //��ʱ��0 TL0����ֵ�Ĵ����
  SIN_EXT uchar sinCodeCount;	//Sin����ȡ����λ���� 
  SIN_EXT void timer0_init(double timer0Delay); //timer0��ʼ����������λΪus
  SIN_EXT void dac0832_init(void);		        //0832��ʼ������
  SIN_EXT void writeDAC0832(uchar dacDate);	    //0832����д�뺯��
#endif