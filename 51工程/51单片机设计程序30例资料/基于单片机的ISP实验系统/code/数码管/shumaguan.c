/**********************************************************
*�ļ����ƣ�shumaguan.c
*�ļ����ܣ��������ʾ��������
*�汾��	   V0.0.0
*���ߣ�	   yd
*ʱ�䣺	   09.07.22
*˵��������������ݿڲ����߶�����оƬ74LS47��Ƭѡ�ڲ���
       ����оƬ7445    
**********************************************************/
#include <AT89X52.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int
enum PORT8255 { PA8255 =0x01,PB8255 =0x02,PC8255 =0x03};  //8255�����˿�ģʽѡ��
#define  PORT8255  P0						//8255���ݶ˿�
#define  CS8255()  {P2_5 =0;P2_6 =1;P2_7 =0;}   //Ƭѡ8255   
#define  PAADDRESS  0x00                    //8255PA�ڲ�����ַ
#define  PBADDRESS  0x01					//8255PB�ڲ�����ַ
#define  PCADDRESS  0x02					//8255PC�ڲ�����ַ
#define  CONADDRESS 0x03                    //8255���ƼĴ�����ַ
/******************************************************
*�˴���������ݼ����ƿ�Ϊ8255��չ�Ķ˿�
//---------------������������ݼ����ƶ˿�----------
#define LED_DATA_A   PB0   
#define LED_DATA_B	 PB1
#define LED_DATA_C	 PB2
#define LED_DATA_D	 PB3
//A-DΪ0001ʱ��ʾ1
#define LED_CS_A	 PB4
#define LED_CS_B	 PB5
#define LED_CS_C	 PB6
#define LED_CS_D	 PB7
******************************************************/
/******************************************************
*�������ƣ�write8255(uchar portMode,uchar c)
*�������ܣ���8255ĳ���˿�д����
*��ڲ�����portMode���˿�ѡ��;c��Ҫд������
*���ڲ�������
******************************************************/
void write8255(uchar portMode,uchar c)
{
  switch(portMode)
  {
    CS8255();
    case  PA8255:   //��PA��д����
	{
	  XBYTE[CONADDRESS] =0x80;   //8255��PA�ڹ����ڷ�ʽ0�����״̬
	  XBYTE[PAADDRESS]  =c;     //�˿�PAд����
	  break;
	}
	case  PB8255:  //��PB��д����
	{
	  XBYTE[CONADDRESS] =0x00;   //8255��PB�ڹ����ڷ�ʽ0�����״̬
	  XBYTE[PBADDRESS]  =c;     //�˿�PBд����
	  break;
	}
	case  PC8255:  //��PC��д����
	{
	  XBYTE[CONADDRESS] =0x00;   //8255��PC�ڹ����ڷ�ʽ0�����״̬
	  XBYTE[PCADDRESS]  =c;     //�˿�PCд����
	  break;
	}
	default:
	  break;
  }
}
/******************************************************
*�������ƣ�read8255(uchar portMode)
*�������ܣ���8255ĳ���˿ڶ�ȡ����
*��ڲ�����portMode���˿�ѡ��
*���ڲ��������ض˿ڶ�ȡ������
******************************************************/
uchar read8255(uchar portMode)
{
  uchar c;
  switch(portMode)
  {
    CS8255();
    case  PA8255:   //��PA��д����
	{
	  XBYTE[CONADDRESS] =0xa0;   //8255��PA�ڹ����ڷ�ʽ0�����״̬
	  c =XBYTE[PAADDRESS];     //�˿�PAд����
	  break;
	}
	case  PB8255:  //��PB��д����
	{
	  XBYTE[CONADDRESS] =0x02;   //8255��PB�ڹ����ڷ�ʽ0�����״̬
	  c =XBYTE[PBADDRESS];      //�˿�PBд����
	  break;
	}
	case  PC8255:  //��PC��д����
	{
	  XBYTE[CONADDRESS] =0x11;   //8255��PC�ڹ����ڷ�ʽ0�����״̬
	  c =XBYTE[PCADDRESS];     //�˿�PCд����
	  break;
	}
	default:
	  break;
  }
  return c;
}
/******************************************************
*�������ƣ�writeLed(uchar cs,uchar data)
*�������ܣ���������������c
*��ڲ�����c��Ҫ���������
*���ڲ�������
******************************************************/
void writeLed(uchar cs,uchar display)
{
  uchar c;
  c =cs;
  c =c<<4;
  c =c&0xf0;
  display =display&0x0f;
  c =display|c;
  write8255(PB8255,c);  //��Ƭѡ��Ҫ��ʾ�����������8255��PB��
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