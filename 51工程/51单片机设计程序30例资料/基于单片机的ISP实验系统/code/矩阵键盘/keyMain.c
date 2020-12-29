/*****************************************************
*�ļ����ƣ�keyMain.c
*�ļ����ܣ�ʵ������ɨ�����
*�汾��	   V0.0.1
*���ߣ�	   yd
*ʱ�䣺	   09.07.22
*˵�������̲����жϷ��������м�����ʱ�������ⲿ�ж�0
******************************************************/
#include <AT89X52.h>
#include <absacc.h>
#include "8255.h"
#define uchar unsigned char
#define uint  unsigned int
#define sei() (EA=1)
#define cli() (EA=0)
//-----------------����ģʽѡ��----------------
#define KEY_MODE  1	  //ģʽѡ��1����ʹ�ñ������;0����ʹ�þ������
uchar keyCurrentValue;
/*************************************************
*�������ƣ�extern0Init(void) 
*�������ܣ��ⲿ�ж�0��ʼ��
*��ڲ�������
*���ڲ�������
*************************************************/
void extern0Init(void) 
{
    EX0 = 1;	 //�ⲿ�ж�0ʹ��
    IT0 = 1;	 //�ⲿ�ж�0�����ж�
}
/************************************************
*�������ƣ�get_key_value(void)
*�������ܣ���ȡ��ֵ
*��ڲ�������
*���ڲ��������ؼ�ֵ1~16
************************************************/
uchar get_key_value(void)
{
   register uchar i;
   uchar line,keyTemp,temp;
   CHOOSE8255();
//   XBYTE[COMMAND_ADDRESS] =0x81; //PC0~3���뷽ʽ��PC4~7�����ʽ
   temp=0xef;     //1110
   for(i=0;i<4;i++)
   {
     XBYTE[COMMAND_ADDRESS] =0x80; //PC0~3�����ʽ��PC4~7�����ʽ
     XBYTE[PC_ADDRESS] =temp;   //1110 
     XBYTE[COMMAND_ADDRESS] =0x81; //PC0~3���뷽ʽ��PC4~7�����ʽ
     line =XBYTE[PC_ADDRESS];	  //��ȡ��
	 if((line&0x0f)!=0x0f)	      //��⵽��
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
  extern0Init(); //�ⲿ�ж�0��ʼ��
  sei();
  while(1);
}
/***********************************************
*�������ܣ��ⲿ�ж�0�жϴ�����
************************************************/
void init0() interrupt 0 
{
  #if KEY_MODE    //���ñ����̷�ʽ
    CHOOSE8255(); //ѡ��8255
	XBYTE[COMMAND_ADDRESS] =0x81; //PC0~3���뷽ʽ,��ʽ0
	keyCurrentValue =XBYTE[PC_ADDRESS];
	keyCurrentValue =keyCurrentValue &0x0f;
  #else			  //���þ������ʽ
    uchar line;
	uchar row;
	keyCurrentValue=get_key();
  #endif
}