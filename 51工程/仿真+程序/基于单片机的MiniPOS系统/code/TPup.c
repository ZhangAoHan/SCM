#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char

sbit BUSY=P2^6;
sbit STB=P2^7;

void topin(uchar *p) 
{
	while(*p!='\0')
		{
			while(BUSY!=0); //查询打印机状态
			P0=*p;          //输出字符
			STB=0;          //模拟STB脉冲
      p++;
		}
}

void main()
{
  uchar idata prn[]="welcome";  //打印 welcome 字符串
	toprn(prn); 
}
	                    
	                     