//**************************************************************
/*****************双机通信主机程序******************************
*双机通信协议简介：
1.主机发送从机地址,例如0x01;
2.从机回复地址数据0x01;
3.主机发送字符长度len;
4.从机回复len;
5.主机发送字符串。
*版本：0.0.1
*作者：kxm
*时间：09.06.10
***************************************************************/
//**************************************************************
#include "target.h"
#include "key.h"
#define REG_MAX 10        //缓冲区最大值
uchar sendBuff[REG_MAX];  //串口缓冲区
/********************************************************
*函数名称：send_data_package(uchar address,uchar sendLen)
*函数功能：向从机发送一个数据包
*函数入口：从机地址address,发送数据长度sendLen
*函数出口：无
*说明：启动数据包发送时，应将数据放缓冲区内
*********************************************************/
void send_data_package(uchar address,uchar sendLen)
{
  uchar temp;
  uchar i;
  TB8=1;                //发送地址数据 
  send_char(address);
  delay_us(10);
  temp=get_char();     //读取从机地址数据回复
  if(temp!=address)    //若回复和发送不同，函数返回
    return;
  TB8=0;               //发送数据长度
  send_char(sendLen);
  delay_us(10);
  temp=get_char();
  if(temp!=sendLen)
    return;
  for(i=0;i<sendLen;i++)
    send_char(sendBuff[i]);
}
void main()
{
	uchar keyValueRead;
	uchar keyReg[2]={0x00,0x00};
	uchar c;
	usart0_initial();	  //串口初始化
	init_key();			  //按键初始化
	while(1)
		{
		   keyValueRead=get_key_value();
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
			 if(keyValueRead==KEY_FIVE)
			   c=0x05;
			 keyReg[1]=keyReg[0];
			 keyReg[0]=c;
			 sendBuff[0]=keyReg[0];	       //将发送给地址为0x02的从机的内容放入发送缓冲
			 send_data_package(0x02,0x01); //将缓冲区内容发给0x02从机
			 sendBuff[0]=keyReg[1];		   //将发送给地址为0x01的从机的内容放入发送缓冲
			 send_data_package(0x01,0x01); //将缓冲区内容发给0x01从机
		   }
		 }	   
}

