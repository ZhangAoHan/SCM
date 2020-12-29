/****************************************************
*文件名称：蜂鸣器测试程序文件
*文件功能：测试实验系统中的蜂鸣器
*版本：	   V0.0.0
*作者：	   yd
*时间：	   09.07.22
****************************************************/
#include <AT89X52.h>
#define uchar unsigned char 
#define uint  unsigned int
//---------定义蜂鸣器端口------------
#define BELL_OUT P1_4
//------------------------------------
void delay(uint i)
{
   uchar a,b;
   for(a =0;a <i;i++)
   {
     b=100;
     while(b)
	 {
	   b--;
	 }
   }
}
void main(void)
{
  while(1)
  {
     BELL_OUT =1;  //打开蜂鸣器
	 delay(100);  
	 BELL_OUT =0;  //关闭蜂鸣器 
  } 
}