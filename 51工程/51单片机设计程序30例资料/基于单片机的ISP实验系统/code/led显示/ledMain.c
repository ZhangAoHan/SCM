/******************************************************
*文件名称：ledMain.c
*文件功能：led显示函数
*版本：	   V0.0.0
*作者：	   yd
*时间：	   09.07.22
*说明：led跑马灯方式显示，数据口通过8255扩展
******************************************************/
#include <AT89X51.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int
#define sei() (EA=1)	//开总中断
#define cli() (EA=0)	//关总中断
enum PORT8255 { PA8255 =0x01,PB8255 =0x02,PC8255 =0x03};  //8255操作端口模式选择
#define  PORT8255  P0									  //8255数据端口
#define  CS8255()  {P2_5 =0;P2_6 =1;P2_7 =0;}   	      //片选8255   
#define  PAADDRESS  0x00                    		      //8255PA口操作地址
#define  PBADDRESS  0x01							      //8255PB口操作地址
#define  PCADDRESS  0x02							      //8255PC口操作地址
#define  CONADDRESS 0x03                    		      //8255控制寄存器地址
uchar  loopVar;          //循环变量
uchar  timer0Count;	     //定时器0溢出中断
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
/**************************************
*函数名称：timer0Init(void)
*函数功能：定时器0初始化,定时10ms
*入口参数：无
*出口参数：无
**************************************/
void timer0Init(void)
{
   TMOD |= 0x01;                        //GATE=0,TR=1运行;C/T=1,counter,0,timer;01十六进制  
   TH0 = 0xdc;
   TL0 = 0x00;
   TR0 = 1;	                            //timer0 控制位，为1时启动timer0
   ET0 = 1;                             //timer0 中断使能 
}
void main()
{
  timer0Init();	             //定时器0初始化，定时10ms
  loopVar=0xfe;
  timer0Count=0x00;
  write8255(PA8255,loopVar); //通过8255输出，led显示
  sei();
  while(1);
}
/********************************************************************************************
* 函数名称：定时器0中断函数
* 功    能：定时器0溢出中断入口处,定时10ms
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void timer0_overflow(void) interrupt 1 
{
   TH0 = 0xdc;
   TL0 = 0x00;
   if(timer0Count<50)   //定时0.5秒
     timer0Count++;
   else
   {
     timer0Count =0x00;
	 if(loopVar&0x80)	            //是否移到最高位
	 {
	   	loopVar =loopVar <<1;
	    loopVar =loopVar &0x01;
	 }
	 else
	 {
	   	loopVar=0xfe;
	 }
	 write8255( PA8255,loopVar);    //数码管循环移位显示
   }
   sei();
}