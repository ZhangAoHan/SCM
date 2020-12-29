/**********************************************************
*文件名称：shumaguan.c
*文件功能：数码管显示驱动函数
*版本：	   V0.0.0
*作者：	   yd
*时间：	   09.07.22
*说明：本数码管数据口采用七段译码芯片74LS47，片选口采用
       译码芯片7445    
**********************************************************/
#include <AT89X52.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int
enum PORT8255 { PA8255 =0x01,PB8255 =0x02,PC8255 =0x03};  //8255操作端口模式选择
#define  PORT8255  P0						//8255数据端口
#define  CS8255()  {P2_5 =0;P2_6 =1;P2_7 =0;}   //片选8255   
#define  PAADDRESS  0x00                    //8255PA口操作地址
#define  PBADDRESS  0x01					//8255PB口操作地址
#define  PCADDRESS  0x02					//8255PC口操作地址
#define  CONADDRESS 0x03                    //8255控制寄存器地址
/******************************************************
*此处数码管数据及控制口为8255扩展的端口
//---------------定义数码管数据及控制端口----------
#define LED_DATA_A   PB0   
#define LED_DATA_B	 PB1
#define LED_DATA_C	 PB2
#define LED_DATA_D	 PB3
//A-D为0001时显示1
#define LED_CS_A	 PB4
#define LED_CS_B	 PB5
#define LED_CS_C	 PB6
#define LED_CS_D	 PB7
******************************************************/
/******************************************************
*函数名称：write8255(uchar portMode,uchar c)
*函数功能：向8255某个端口写数据
*入口参数：portMode，端口选择;c，要写的数据
*出口参数：无
******************************************************/
void write8255(uchar portMode,uchar c)
{
  switch(portMode)
  {
    CS8255();
    case  PA8255:   //向PA口写数据
	{
	  XBYTE[CONADDRESS] =0x80;   //8255的PA口工作在方式0，输出状态
	  XBYTE[PAADDRESS]  =c;     //端口PA写数据
	  break;
	}
	case  PB8255:  //向PB口写数据
	{
	  XBYTE[CONADDRESS] =0x00;   //8255的PB口工作在方式0，输出状态
	  XBYTE[PBADDRESS]  =c;     //端口PB写数据
	  break;
	}
	case  PC8255:  //向PC口写数据
	{
	  XBYTE[CONADDRESS] =0x00;   //8255的PC口工作在方式0，输出状态
	  XBYTE[PCADDRESS]  =c;     //端口PC写数据
	  break;
	}
	default:
	  break;
  }
}
/******************************************************
*函数名称：read8255(uchar portMode)
*函数功能：从8255某个端口读取数据
*入口参数：portMode，端口选择
*出口参数：返回端口读取的数据
******************************************************/
uchar read8255(uchar portMode)
{
  uchar c;
  switch(portMode)
  {
    CS8255();
    case  PA8255:   //向PA口写数据
	{
	  XBYTE[CONADDRESS] =0xa0;   //8255的PA口工作在方式0，输出状态
	  c =XBYTE[PAADDRESS];     //端口PA写数据
	  break;
	}
	case  PB8255:  //向PB口写数据
	{
	  XBYTE[CONADDRESS] =0x02;   //8255的PB口工作在方式0，输出状态
	  c =XBYTE[PBADDRESS];      //端口PB写数据
	  break;
	}
	case  PC8255:  //向PC口写数据
	{
	  XBYTE[CONADDRESS] =0x11;   //8255的PC口工作在方式0，输出状态
	  c =XBYTE[PCADDRESS];     //端口PC写数据
	  break;
	}
	default:
	  break;
  }
  return c;
}
/******************************************************
*函数名称：writeLed(uchar cs,uchar data)
*函数功能：向数码管输出数据c
*入口参数：c，要输出的数据
*出口参数：无
******************************************************/
void writeLed(uchar cs,uchar display)
{
  uchar c;
  c =cs;
  c =c<<4;
  c =c&0xf0;
  display =display&0x0f;
  c =display|c;
  write8255(PB8255,c);  //将片选和要显示的数据输出到8255的PB口
}
void main()
{
  uchar i;
  while(1)
  {
    for(i=0;i<8;i++)
	{
	  writeLed(i,0x01);
	}
  }
}