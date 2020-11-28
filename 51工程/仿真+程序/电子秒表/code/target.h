/*****************************************************
*�ļ����ƣ�target.h
*�ļ����ܣ�������target.c�����ļ��У�ʵ���ض�������
��ʵ�ֺ�Ӧ��
*���ߣ�yd
*ʱ�䣺09.06.20
*****************************************************/
#ifndef TARGET_H
#define TARGET_H 1
  #include "Include.h"
  #ifndef TARGET_GLOBAL
    #define TARGET_EXT extern
  #else
    #define TARGET_EXT
  #endif
/**********����ʱ���λ��ʱ�������е�λ��**********/
  #define MIN_H 0   //���Ӽ���ʮλ��ʱ�������0λ
  #define MIN_L 1	//���Ӽ�����λ��ʱ�������1λ
  #define S_H   3	//�����ʮλ��ʱ���������λ
  #define S_L   4	//�������λ��ʱ���������λ
  #define MS_H   6	//�������ʮλ��ʱ���������λ
  #define MS_L   7	//���������λ��ʱ���������λ
/*************************************************/
  #define CLEAR_KEY  P3_6   //������㰴���˿�ӳ��
  TARGET_EXT void target_init(void);
  TARGET_EXT void timer0_init(void);       //timer0��ʼ��
  TARGET_EXT void int0_init(void);	       //int0��ʼ��
  TARGET_EXT void int1_init(void);	       //int1��ʼ��
  TARGET_EXT void ms_to_s(uchar *clockS);     //��λ�������,�뼶��λ
  TARGET_EXT void s_to_min(uchar *clockMin);  //�뼶����Ӽ���λ
#endif