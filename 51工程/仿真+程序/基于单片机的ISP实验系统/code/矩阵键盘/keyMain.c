/*****************************************************
*文件名称：keyMain.c
*文件功能：实验板键盘扫描测试
*版本：	   V0.0.1
*作者：	   yd
*时间：	   09.07.22
*说明：键盘采用中断法，即当有键按下时将触发外部中断0
******************************************************/
#include <AT89X52.h>
#include <absacc.h>
#include "8255.h"
#define uchar unsigned char
#define uint  unsigned int
#define sei() (EA=1)
#define cli() (EA=0)
//-----------------键盘模式选择----------------
#define KEY_MODE  1	  //模式选择，1代表使用编码键盘;0代表使用矩阵键盘
uchar keyCurrentValue;
/*************************************************
*函数名称：extern0Init(void) 
*函数功能：外部中断0初始化
*入口参数：无
*出口参数：无
*************************************************/
void extern0Init(void) 
{
    EX0 = 1;	 //外部中断0使能
    IT0 = 1;	 //外部中断0跳变中断
}
/************************************************
*函数名称：get_key_value(void)
*函数功能：获取键值
*入口参数：无
*出口参数：返回键值1~16
************************************************/
uchar get_key_value(void)
{
   register uchar i;
   uchar line,keyTemp,temp;
   CHOOSE8255();
//   XBYTE[COMMAND_ADDRESS] =0x81; //PC0~3输入方式，PC4~7输出方式
   temp=0xef;     //1110
   for(i=0;i<4;i++)
   {
     XBYTE[COMMAND_ADDRESS] =0x80; //PC0~3输出方式，PC4~7输出方式
     XBYTE[PC_ADDRESS] =temp;   //1110 
     XBYTE[COMMAND_ADDRESS] =0x81; //PC0~3输入方式，PC4~7输出方式
     line =XBYTE[PC_ADDRESS];	  //读取行
	 if((line&0x0f)!=0x0f)	      //检测到行
	 {
	   for(line=0;line<4;line++)
	   {
	      if((line &0x01)==0x00)
		  {
			break;
		  }
		  else
		  {
		    line=line>>1;
		  }
	   }
	   keyTemp=i+1+line*4;
	   return keyTemp;
	 }
	 temp =temp<<1;
	 temp =temp |0x01;
   }
   return keyTemp;
}
void main()
{
  keyCurrentValue=0x00;
  extern0Init(); //外部中断0初始化
  sei();
  while(1);
}
/***********************************************
*函数功能：外部中断0中断处理函数
************************************************/
void init0() interrupt 0 
{
  #if KEY_MODE    //采用编码盘方式
    CHOOSE8255(); //选中8255
	XBYTE[COMMAND_ADDRESS] =0x81; //PC0~3输入方式,方式0
	keyCurrentValue =XBYTE[PC_ADDRESS];
	keyCurrentValue =keyCurrentValue &0x0f;
  #else			  //采用矩阵键盘式
    uchar line;
	uchar row;
	keyCurrentValue=get_key();
  #endif
}