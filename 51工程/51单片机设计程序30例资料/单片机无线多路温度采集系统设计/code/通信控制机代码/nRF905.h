/***********************************************************************
*文件名称：nRF905.h
*说明：本文件为无线通信器件nRF905驱动函数头文件
*功能：1.端口定义
       2.驱动函数声明
*修改：无
*版本：V1.0.0
*作者：YuanDong
*时间：2009.07.03
*************************************************************************/
#ifndef __NRF905_H_
#define __NRF905_H_
#include "Include.h"
#ifndef _NRF905_GLOBAL_
   #define NRF_EXT extern
#else 
   #define NRF_EXT
#endif
/*****************nRF905管脚定义*********************/
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
/***nRF905 Spi接口指令的宏定义,全部从对应寄存器的字节0开始***/
#define WC		0x00	// Write configuration register command 写配置寄存器
#define RC		0x10 	// Read  configuration register command 读配置寄存器
#define WTP		0x20 // Write TX Payload  command 向TX-Payload寄存器写入发送有效数据
#define RTP		0x21	// Read  TX Payload  command 从TX-Payload寄存器读取发送有效数据
#define WTA		0x22	// Write TX Address  command 向TX-Address寄存器写入发送地址
#define RTA		0x23	// Read  TX Address  command 从TX-Address寄存器读取发送地
#define RRP		0x24	// Read  RX Payload  command 从RX-Payload寄存器读取接收到的有效数据
/*****************变量定义***************************/
NRF_EXT  unsigned char TxdBuf[5];		//发送数据缓冲区
NRF_EXT  unsigned char RxdBuf[5];		//接收数据缓冲区
/*****************函数声明***************************/
NRF_EXT void nRF905_Init(void);            /*nRF905初始化*/
NRF_EXT void nRF905_SendData(void);        /*nRF905发送数据*/
NRF_EXT void nRF905_ReceiveData(void);     /*nRF905接收数据*/
#endif
