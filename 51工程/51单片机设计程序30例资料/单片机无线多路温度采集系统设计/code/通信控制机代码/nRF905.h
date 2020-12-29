/***********************************************************************
*�ļ����ƣ�nRF905.h
*˵�������ļ�Ϊ����ͨ������nRF905��������ͷ�ļ�
*���ܣ�1.�˿ڶ���
       2.������������
*�޸ģ���
*�汾��V1.0.0
*���ߣ�YuanDong
*ʱ�䣺2009.07.03
*************************************************************************/
#ifndef __NRF905_H_
#define __NRF905_H_
#include "Include.h"
#ifndef _NRF905_GLOBAL_
   #define NRF_EXT extern
#else 
   #define NRF_EXT
#endif
/*****************nRF905�ܽŶ���*********************/
sbit  TX_EN  = P1^0;
sbit  PWR    = P1^1;
sbit  CD     = P1^2;
sbit  SCK    = P1^3;
sbit  MISO   = P1^4;
sbit  MOSI   = P1^5;
sbit  CSN    = P1^6;
sbit  AM     = P1^7;
sbit  uCK    = P2^0;
sbit  TRX_CE = P1^1;
sbit  DR     = P1^2;
/***nRF905 Spi�ӿ�ָ��ĺ궨��,ȫ���Ӷ�Ӧ�Ĵ������ֽ�0��ʼ***/
#define WC		0x00	// Write configuration register command д���üĴ���
#define RC		0x10 	// Read  configuration register command �����üĴ���
#define WTP		0x20 // Write TX Payload  command ��TX-Payload�Ĵ���д�뷢����Ч����
#define RTP		0x21	// Read  TX Payload  command ��TX-Payload�Ĵ�����ȡ������Ч����
#define WTA		0x22	// Write TX Address  command ��TX-Address�Ĵ���д�뷢�͵�ַ
#define RTA		0x23	// Read  TX Address  command ��TX-Address�Ĵ�����ȡ���͵�
#define RRP		0x24	// Read  RX Payload  command ��RX-Payload�Ĵ�����ȡ���յ�����Ч����
/*****************��������***************************/
NRF_EXT  unsigned char TxdBuf[5];		//�������ݻ�����
NRF_EXT  unsigned char RxdBuf[5];		//�������ݻ�����
/*****************��������***************************/
NRF_EXT void nRF905_Init(void);            /*nRF905��ʼ��*/
NRF_EXT void nRF905_SendData(void);        /*nRF905��������*/
NRF_EXT void nRF905_ReceiveData(void);     /*nRF905��������*/
#endif
