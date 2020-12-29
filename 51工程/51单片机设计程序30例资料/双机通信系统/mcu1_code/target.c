#define TARGET_GLOBAL 1
#include "target.h"
/*********************************************
*函数名称：usart0_Initial(void)
*函数功能：初始化串口
*入口函数：无
*出口函数：无
*********************************************/
void usart0_Initial(void)
{ 
/************TH1=256-(K*oscFreq)/384*BaudRate************/
	SCON=0x50;   //SM0=0;SM1=1;REN=1;
	TI=0;        //数据发送状态清零
	RI=0;		 //数据接收状态清零 
	PCON=0;		 //不加倍
	TH1=0xF3;	 //bode=2400
	TL1=0XF3;
	TMOD=0X20;	 //TIMER1 MODER2;
	ET1=0;		 //屏蔽timer1溢出中断
	TR1=1;		 //启动timer1
	ES=0;		 //屏蔽串口中断
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
   SBUF=txd;
   while(!TI);				// 等特数据传送
   TI=0;					// 清除数据传送标志
}
/********************************************
*函数名称：send_str(uchar *str,uchar len)
*函数功能：串口发送一行字符串
*函数入口：字符串指针*str，字符串长度len
*函数出口：无
********************************************/
void send_str(uchar *str,uchar len)
{
  uchar i;
  for(i=0;i<len;i++)
   send_char(str[i]);
}
/********************************************
*函数名称：get_char(void)
*函数功能：串口接收一个字符
*函数入口：串口发送的字符rxd
*函数出口：无
********************************************/
uchar get_char(void)
{
   uchar temp;
   RI=0;
   while(!RI);	 // 等特数据传送
   temp=SBUF;
   RI=0;		 // 清除数据传送标志 
   return temp;
}
            