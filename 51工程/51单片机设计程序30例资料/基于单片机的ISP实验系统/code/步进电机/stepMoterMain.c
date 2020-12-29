/******************************************************
*�ļ����ƣ�stepMoterMain.c
*�ļ����ܣ�ʵ����в���������ֲ��Գ���
*�汾��    V0.0.1
*���ߣ�    yd
*ʱ�䣺    09.07.22
*˵�����˴��������L298�������˲��Գ���ְ˲������ĸ���
���Ĳ������
******************************************************/
#include <AT89X52.h>
#include <absacc.h>
#include "8255.h"	
#define uchar unsigned char
#define uint  unsigned int
/********************************************************************************************
* �������ƣ�Delay(uint a)
* ��    �ܣ��ӳ�ʱ��=a*1ms
* ��ڲ�����
* ���ڲ�������
*********************************************************************************************/
void Delay(uint a)
{
   uchar  i;
   while(a--)
   for(i=0;i<125;i++);
}
/*******************************************************
*�������ƣ�ground(step)
*�������ܣ���������ĸ��༫���ź�
*������ڣ�step,�����λ�ĵڼ���
*�������ڣ���
*˵�����������ת�������ְ˲�
*******************************************************/
void ground(step) 
{
  CHOOSE8255();
  XBYTE[COMMAND_ADDRESS] =0x00; //PA�����ڷ�ʽ0�������ʽ
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
