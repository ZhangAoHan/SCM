/*******************************************************************************
* �ļ����ƣ�Include.h                          
* ˵�������ļ�ΪInclude.hͷ�ļ�
* ���ܣ� 
* �޸ģ� ��
* �汾��1.0.0
* ���ߣ�YuanDong 
* ʱ�䣺2009.5.30 
*******************************************************************************/
#ifndef INCLUDE_H
#define INCLUDE_H
  #include "AT89X51.h"
  #include "intrins.h"
  #define  uchar unsigned  char
  #define  uint  unsigned  int
  #define  _BV(x)          (1<<(x))
  #define  GET_BIT(x,y)    (((x)&(1<<(y)))==0?0:1)               //ȡx����yλ������
  #define  SET_BIT(x,y)    ((x)|=(0x0001<<(y)))	              //��λx����yλ
  #define  CLR_BIT(x,y)    ((x)&=~(0x0001<<(y)))               //����x����yλ
  #define  LET_BIT(x,y,z)   ((x)=(x)&(~(0x0001<<(y)))|(z)<<(y))    //��λ������x����yλ
  #define  sei()    (EA=1)	                                //�����ж�
  #define  cli()    (EA=0)	                                //�����ж�
#endif
