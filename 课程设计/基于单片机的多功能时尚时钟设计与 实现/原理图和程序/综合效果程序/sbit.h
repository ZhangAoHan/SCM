#ifndef __sbit_H__
#define __sbit_H__


#include <NEW_8051.H>
#include <intrins.h>

sbit STRA=P4^3;	 //锁存
sbit OEA=P3^4;  //595使能
sbit SDAA =P3^0;	 //数据
sbit SCKA=P3^1;  //时钟

sbit STRB=P1^5;	 //锁存
sbit OEB=P1^4;  //595使能
sbit SDAB=P1^6;	//数据
sbit SCKB=P1^7;	//时钟

sbit STRC=P1^1;	 //锁存
sbit OEC=P1^0;  //595使能
sbit SDAC=P1^2;	//数据
sbit SCKC=P1^3;	//时钟


sbit T_CLK=P3^5;		    //DS1302引脚连接
sbit T_IO =P3^6;
sbit T_RST=P3^7;
sbit LED=P0^3;	//最外圈LED控制
#define Auto_adder 0XC8//保存手动 自动调整 标志
#define DISP_TIME_adder_L 0XC2	//显示模拟表盘时钟单列时间
#define DISP_TIME_adder_H 0XC4
extern void Round_table(uchar DISP_LINEE,uchar HourE,uchar CentE,uchar SecE );
extern void Send_data_A(unsigned char temp);	  /*从串口发送数据*/
extern void Send_data_B(unsigned char temp);	  /*发送数据*/
extern void Send_data_C(unsigned char temp);
extern void dis_picture(uchar temp_one,uchar temp_two,uchar temp_three,uchar temp_four);
extern void Send_data(unsigned char d);
extern uchar byte_read(uint);
extern void sector_erase(uint);
extern void byte_program(uint, uchar);
extern bit Scan_bit;
extern void   RTInputByte(uchar);         //* 输入 1Byte */
extern uchar  RTOutputByte(void);         //* 输出 1Byte */
extern void   W1302(uchar, uchar);        // 向DS1302写入一个字节
extern uchar  R1302(uchar);               // 从DS1302读出一个字节
extern void   Set1302(uchar *pClock);
extern void   du1302();                   // 读时间  
extern void   DelayMs(void);              // 延时
extern void   Set(uchar,uchar );          // 变量调整
extern uchar starts_time[7];
extern void  write_1302Data (uchar  ucAddr,uchar  Value);
extern uint uiFontNumber;//字幕总数
extern uchar uiFontNumber_P;
extern uchar uiFontNumber_D;
extern void Auto_Set1302(uchar *pClock);
extern uint Pt;
extern bit Auto;
#endif