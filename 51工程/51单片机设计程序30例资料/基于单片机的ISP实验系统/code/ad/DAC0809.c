/************************************************
*文件名称：ADC0809.c
*文件功能：实验板上ad转换芯片0809测试程序
*版本：    V0.0.1
*作者：    yd
*时间：    09.07.22
************************************************/
#include <AT89X52.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int
//-------------adc0809端口定义--------------------
#define CHOOSE0809()  {P2_5=0;P2_6=1;P2_7=1;} //定义0809片选端
#define PORT_ADC0809  P0                      //0809数据端口
//------------------------------------------------
/****************************************************
*函数名称：channelChoose(uchar channel)
*函数功能：0809转换通道选择
*入口参数：channel,通道选择
*出口参数：返回通道采样数据 
****************************************************/
uchar channelChoose(uchar channel)
{
  uchar temp;
  CHOOSE0809();
  XBYTE[channel-1] =0x00;  //选择通道，等待转换
  while(P3_3==1);  //等待转换
  temp =P0;
  return temp;
}
void main()
{
  uchar temp;
  while(1)
  { 
    temp =channelChoose(0x01);  //读取通道1
  }
}