/*****************************************************************************************
*文件名称：serial.c
*说明：本文件为串口通信驱动函数文件
*功能：1.端口定义
       2.驱动函数声明
*修改：无
*版本：V1.0.0
*作者：YuanDong
*时间：2009.07.03
*****************************************************************************************/
#define  SERIAL_GLOBAL 1
#include "serial.h"
/*****************************************************************************************
*函数名称：serial_Init(void)
*函数功能：初始化串口
*函数入口：无
*函数出口：无
*说明：波特率2400
*****************************************************************************************/
void serial_Init(void)
{ 
/************TH1=256-(K*oscFreq)/384*BaudRate************/
	SCON=0x50;   //SM0=0;SM1=1;REN=1;
	TI=0;        //数据发送状态清零
	RI=0;		     //数据接收状态清零 
	PCON=0;		   //不加倍
	TH1=0xF3;	   //bode=2400
	TL1=0XF3;
	TMOD=0X20;	 //TIMER1 MODER2;
	ET1=0;		   //屏蔽timer1溢出中断
	TR1=1;		   //启动timer1
	ES=0;		     //屏蔽串口中断
}
/*****************************************************************************************
*函数名称：serial_PutChar(uchar sendChar) 
*函数功能：串口发送一个字符
*函数入口：要发送的一个字符sendChar
*函数出口：无
*****************************************************************************************/
void serial_PutChar(uchar sendChar) 
{
   TI=0;
   SBUF=txd;
   while(!TI);				// 等特数据传送
   TI=0;					    // 清除数据传送标志
}
/*****************************************************************************************
*函数名称：serial_PutStr(uchar *str,uchar len)
*函数功能：串口发送一行字符串
*函数入口：字符串指针*str，字符串长度len
*函数出口：无
*****************************************************************************************/
void serial_PutStr(uchar *str,uchar len)
{
  uchar i;
  for(i=0;i<len;i++)
   send_char(str[i]);
}
/*****************************************************************************************
*函数名称：serial_GetChar(void)
*函数功能：串口接收一个字符
*函数入口：串口发送的字符rxd
*函数出口：无
*****************************************************************************************/
uchar serial_GetChar(void)
{
   uchar temp;
   RI=0;
   while(!RI);	 // 等特数据传送
   temp=SBUF;
   RI=0;		     // 清除数据传送标志 
   return temp;
}
