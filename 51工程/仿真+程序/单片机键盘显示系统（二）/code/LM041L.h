/*******************************************************************************
* 文件名称：LM041L.h                          
* 说明：本文件为LCD头文件
* 功能：1. LCD端口定义
2. LCD用到的函数说明
* 修改： 
* 版本：1.0.0
* 作者：YuanDong
* 时间：2009.5.11 
*******************************************************************************/

#ifndef LM041L_H
  #define LM041L_H 1
  #include "Include.h"
  #ifndef   LCD_GLOBAL
    #define LCD_EXT extern 
  #else
    #define LCD_EXT     
  #endif 
/***********端口定义************/
  #define LCD_DATA   P0	 
  sbit RS = P2^0;
  sbit RW = P2^1;
  sbit EN = P2^2;
 // uchar x_pos = 0,y_pos = 0;
  
/***********端口定义************/
  enum SEND_DATA_TYPE{DATA=0x01,COMM=0x00};  //发送给LCD的数据为comm或者data
LCD_EXT void delay(uint n);
LCD_EXT void recom(void);                   //读lcd状态指令 
LCD_EXT void busytest(void);		        //测试是否忙
LCD_EXT void wrlcd(uchar mode,uchar n);     //写lcd指令和数据,DATA或者COMM
LCD_EXT void clrscr(void);	                //清屏
LCD_EXT void initlcd(void);			        //初始化lcd
LCD_EXT void setpos(uchar x,uchar y);       //设置光标位置
LCD_EXT void wrstrdat(uchar x,uchar y,uchar *s,uint length);//写字符串数据
#endif