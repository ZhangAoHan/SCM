/*******************************************************************************
* 文件名称：iic.h                          
* 说明：本文件为驱动头文件
* 功能：1.端口定义 
        2.函数说明
* 修改： 无
* 版本：1.0.0
* 作者：YuanDong 
* 时间：2009.7.20 
*******************************************************************************/   
#ifndef _IIC_H
#define _IIC_H
  #ifndef IIC_GLOBAL
     #define IIC_EXT extern
  #else
     #define IIC_EXT
  #endif
//-----------定义IIC总线端口---------------
  sbit scl =P2^0;
  sbit dat =P2^1;
//-----------------------------------------
  IIC_EXT void  iic_write(uchar x);
  IIC_EXT uchar iic_read(void);
#endif
