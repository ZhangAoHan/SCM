/******************************************************
*文件名称：stepMoterMain.c
*文件功能：实验板中步进电机部分测试程序
*版本：    V0.0.1
*作者：    yd
*时间：    09.07.22
*说明：此处电机采用L298驱动，此测试程序分八步驱动四个相
极的步进电机
******************************************************/
#include <AT89X52.h>
#include <absacc.h>
#include "8255.h"	
#define uchar unsigned char
#define uint  unsigned int
/********************************************************************************************
* 函数名称：Delay(uint a)
* 功    能：延迟时间=a*1ms
* 入口参数：
* 出口参数：无
*********************************************************************************************/
void Delay(uint a)
{
   uchar  i;
   while(a--)
   for(i=0;i<125;i++);
}
/*******************************************************
*函数名称：ground(step)
*函数功能：给电机的四个相极送信号
*函数入口：step,电机相位的第几步
*函数出口：无
*说明：步进电机转步数，分八步
*******************************************************/
void ground(step) 
{
  CHOOSE8255();
  XBYTE[COMMAND_ADDRESS] =0x00; //PA工作在方式0，输出方式
  switch(step)
  {
    case 0x00:
	{
	  //MOTER_M1= 1; 
	  //MOTER_M2= 0;
	  //MOTER_M3= 0;
	  //MOTER_M4= 0;
	  XBYTE[PA_ADDRESS] =0x0b; //0/0/M4/M3/1/M2/M1/1
	  break;
	}
	case 0x01:
	{
      //MOTER_M1= 1;
	  //MOTER_M2= 1;
	  //MOTER_M3= 0;
	  //MOTER_M4= 0;
	  XBYTE[PA_ADDRESS] =0x0f; //0/0/M4/M3/1/M2/M1/1
	  break;	  
	}
	case 0x02:
	{
	  //MOTER_M1= 0;
	  //MOTER_M2= 1;
	  //MOTER_M3= 0;
	  //MOTER_M4= 0;
	  XBYTE[PA_ADDRESS] =0x0d; //0/0/M4/M3/1/M2/M1/1
	  break;
	}
	case 0x03:
	{
	  //MOTER_M1= 0;
	  //MOTER_M2= 1;
	  //MOTER_M3= 1;
	  //MOTER_M4= 0;
	  break;
	}
	case 0x04:
	{ 
	  //MOTER_M1= 0;
	  //MOTER_M2= 0;
	  //MOTER_M3= 1;
	  //MOTER_M4= 0;
	  XBYTE[PA_ADDRESS] =0x19; //0/0/M4/M3/1/M2/M1/1
	  break; 
	}
	case 0x05:
	{
	  //MOTER_M1= 0;
	 // MOTER_M2= 0;
	 // MOTER_M3= 1;
	 // MOTER_M4= 1;
	  XBYTE[PA_ADDRESS] =0x39; //0/0/M4/M3/1/M2/M1/1
	  break;
	}
	case 0x06:
	{ 
	  //MOTER_M1= 0;
	  //MOTER_M2= 0;
	  //MOTER_M3= 0;
	  //MOTER_M4= 1;
	  XBYTE[PA_ADDRESS] =0x29; //0/0/M4/M3/1/M2/M1/1
	  break;
	}
	case 0x07:
	{
	  //MOTER_M1= 0;
	  //MOTER_M2= 0;
	  //MOTER_M3= 0;
	  //MOTER_M4= 0;
	  XBYTE[PA_ADDRESS] =0x09; //0/0/M4/M3/1/M2/M1/1
	  break;
	}
	default:
	   break;
  }
}
void main()
{
  uchar moterTemp;
  moterTemp=0x00;
  while(1)
  {
    ground(moterTemp);
	Delay(800);
	if(moterTemp <0x07)
	  moterTemp++;
	else
	  moterTemp =0x00;
  } 
}
