#define TARGET_GLOABAL
#include "target.h"
#define TARGET_GLOBAL 1
#include "target.h"
/*********************************************
*函数名称：usart0_Initial(void)
*函数功能：初始化串口
*入口函数：无
*出口函数：无
*********************************************/
void usart0_init(void)
{
/************TH1=256-(K*oscFreq)/384*BaudRate************/
    SCON=0xF0;   //SM0=1;SM1=1;SM2=1;REN=1;MODER3
	TI=0;        //数据发送状态清零
	RI=0;		 //数据接收状态清零
	RB8=0; 
	PCON=0;		 //不加倍
	TH1=0xFD;	 //bode=9600
	TL1=0XFD;
	TMOD=0X20;	 //TIMER1 MODER2;
	ET1=0;		 //屏蔽timer1溢出中断
	TR1=1;		 //启动timer1
	ES=1;		 //使能串口中断
}
/*********************************************
*函数名称：send_char(uchar txd) 
*函数功能：串口发送一个字符
*入口函数：要发送的一个字符txd
*出口函数：无
*********************************************/
void send_char(uchar txd) 
{
   TI=0;
   ES=0;
   SBUF=txd;
   while(!TI);				// 等特数据传送
   TI=0;					// 清除数据传送标志
   ES=1;
}
/********************************************
*函数名称：send_str(uchar *str,uchar len)
*函数功能：串口发送一行字符串
*入口函数：字符串指针*str，字符串长度len
*出口函数：无
********************************************/
void send_str(uchar *str,uchar len)
{
  uchar i;
  for(i=0;i<len;i++)
   send_char(str[i]);
}