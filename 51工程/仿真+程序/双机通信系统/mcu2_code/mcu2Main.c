#include  "target.h"
#include  "led.h"
const uchar code displayMode=0x00;          //显示模式，数字字符类型
uchar displayBuff[4]={'0','0','0','0'};     //数码管显示缓冲区 
static uchar uart_get_mode;                 //从机处理接收数据阶段记录
void main()
{
   usart0_initial();     //串口初始化
   init_led();			 //led初始化
   uart_get_mode=0x00;	 //从机接收数据处在0阶段
   sei();			     //开中断
	while(1)
	{
      ledSweepDisplay(displayBuff,displayMode,0x04);  
	}
}
/*******串口中断程序********************/
void usart0_get() interrupt 4
{
  uchar temp;
  uchar count,i;
  temp=SBUF;  
  /*******************************************
  *第一阶段,接收校验码
  ********************************************/
  if(uart_get_mode==0x00)  
  {
    if(temp==0xAA)
	{
	  send_char(0xBB);
	}
  }
 /*********************************************
 *第二阶段接收数据长度 ，由于被实例一次传送数据为
 *1个字节，故此时的数据长度为保留状态。
 **********************************************/
  if(uart_get_mode==0x01) 
  {
	  count=temp;
	  send_char(0xBB);
  }
 /********************************************
 *第三阶段接收数据
 *********************************************/
  if(uart_get_mode==0x02) 
  {
    for(i=0;i<3;i++)
	{
	  displayBuff[i]=displayBuff[i+1];
	}
    displayBuff[3]=temp+'0';
	
  }
  if(uart_get_mode<0x02)
    uart_get_mode++;
  else
    uart_get_mode=0x00;
  RI=0;
}