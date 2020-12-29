/*******************************************************************************
* 文件名称：spi.h                          
* 说明：本文件为驱动头文件
* 功能：1.端口定义 
        2.函数说明
* 修改： 无
* 版本：1.0.0
* 作者：YuanDong 
* 时间：2009.7.20 
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
//------------------SPI端口定义----------------------------------
sbit SCK=P1^0;                          // 将p1.0口模拟时钟输出
sbit MOSI=P1^1;                         // 将p1.1口模拟主机输出
sbit MISO=P1^2;                         // 将p1.1口模拟主机输入
sbit SS1=P1^3;                          // 将p1.1口模拟片选 
//----------------------------------------------------------------
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};  //延时函数

SPI_EXT void SPISendByte(unsigned char ch);     //发送一个字节    
SPI_EXT unsigned char SPIreceiveByte(void);     //读一个字节
SPI_EXT unsigned char SPIsend_receiveByte(unsigned char ch); //串行输入输出子程序  
#endif
