/**************************************************
*文件名称：继电器测试程序文件
*文件功能：测试实验系统中的继电器
*版本：V0.0.0
*作者：yd
*时间：09.07.22
**************************************************/
#include <AT89X52.h>
#define uchar unsigned char
#define uint  unsigned int
//-----------定义固态继电器端口------------
#define RELAY_OUT  P3_5
//-----------------------------------------
void delay(uchar i)
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
void main( )
{
   while(1)
  {
     RELAY_OUT =1;  //打开固态继电器
	 delay(100);  
	 RELAY_OUT =0;  //关闭固态继电器 
  } 
}