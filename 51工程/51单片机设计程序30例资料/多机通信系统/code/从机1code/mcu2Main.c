#include "Include.h"
#include "led.h"
#include "target.h"
#define machineAddress 0x01 //本从机地址定义 
uchar displayBuff[2];          //从机显示缓冲区，本从机只有一个显示区
uchar getCharStep;
void main()
{
  usart0_init();
  led_init();
  displayBuff[0]=0x00;
  getCharStep=0x00;
  sei();
  while(1)
  {
    ledWrite(displayBuff[0]+'0',0x01,DIGITAL);
  }
}
void uart_get_char(void) interrupt 4 
{
  uchar temp;
  static count,i;
  temp=SBUF;
  RI=0;
  RB8=0;
  if(getCharStep==0x00)       //第一阶段接收从机地址
  {
    if(temp==machineAddress)  //地址相符
	{
	  send_char(temp);	      //回复主机
	  SM2=0;      		      //进入接收数据阶段
	}
	else
	{
	  return;
	}
  }
  if(getCharStep==0x01)	      //第二阶段接收数据长度
  {
    count=temp;
	send_char(temp);
	i=0x01;
  }
  if(getCharStep==0x02)		  //第三阶段接收数据
  {
    if(i!=count)			  //本实例实际count=0x01,此段程序为扩展接收多个数据使用
	{
	  displayBuff[i-0x01]=temp;
	  i++;
	}
	else					  //接收数据完毕
	{
	  SM2=1;				  //启动地址位接收
	  displayBuff[i-0x01]=temp;
	}	 
  }
  if(getCharStep<0x02)
   getCharStep++; 
  else if(SM2==1)
   getCharStep=0x00;
}