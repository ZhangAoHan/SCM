/*****************双机通信主机程序******************************
*双机通信协议简介：
1.主机发送0xAA;
2.从机回复0xBB;
3.主机发送字符长度len;
4.从机回复0xBB;
5.主机发送字符串。
*版本：0.0.0
*作者：yd
*时间：09.06.07
***************************************************************/
#include "target.h"
#include "key.h"
void send_key_value(uchar keySend)
{
  uchar temp;
  send_char(0xAA);     //发送双机重新协议头字节
  delay_us(10);
  temp=get_char();	   //读取从机回复字节
  if(temp==0xBB)	   //判断是否为0xBB
  {
    send_char(0x01);   //发送的数据长度
	delay_us(10);
	temp=get_char();   //读取从机回复字节
	if(temp==0xBB)	   //判断是否为0xBB
	{
	  send_char(keySend);
	}
  }
}
void main()
{
	uchar c=0;
	uchar keyValueRead;
	usart0_initial();
	init_key();
	while(1)
		{
		   keyValueRead=get_key_value();  //读取按下的按键
		   if(keyValueRead!=KEY_NULL)
		   {
		     if(keyValueRead==KEY_ONE)
			   c=0x01;
			 if(keyValueRead==KEY_TWO)
			   c=0x02;
			 if(keyValueRead==KEY_THREE)
			   c=0x03;
			 if(keyValueRead==KEY_FOUR)
			   c=0x04;
			 send_key_value(c);
		   }
		 }	   
}

