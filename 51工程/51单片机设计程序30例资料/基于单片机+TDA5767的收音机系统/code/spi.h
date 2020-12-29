/*******************************************************************************
* �ļ����ƣ�spi.h                          
* ˵�������ļ�Ϊ����ͷ�ļ�
* ���ܣ�1.�˿ڶ��� 
        2.����˵��
* �޸ģ� ��
* �汾��1.0.0
* ���ߣ�YuanDong 
* ʱ�䣺2009.7.20 
*******************************************************************************/ 
#ifndef _SPI_H
#define _SPI_H 1
#ifndef SPI_GLOBAL 
  #define SPI_EXT extern
#else
  #define SPI_EXT
#endif
 
#include <reg51.h>
#include <intrins.h>
//------------------SPI�˿ڶ���----------------------------------
sbit SCK=P1^0;                          // ��p1.0��ģ��ʱ�����
sbit MOSI=P1^1;                         // ��p1.1��ģ���������
sbit MISO=P1^2;                         // ��p1.1��ģ����������
sbit SS1=P1^3;                          // ��p1.1��ģ��Ƭѡ 
//----------------------------------------------------------------
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};  //��ʱ����

SPI_EXT void SPISendByte(unsigned char ch);     //����һ���ֽ�    
SPI_EXT unsigned char SPIreceiveByte(void);     //��һ���ֽ�
SPI_EXT unsigned char SPIsend_receiveByte(unsigned char ch); //������������ӳ���  
#endif
