/************************************************
*�ļ����ƣ�ADC0809.c
*�ļ����ܣ�ʵ�����adת��оƬ0809���Գ���
*�汾��    V0.0.1
*���ߣ�    yd
*ʱ�䣺    09.07.22
************************************************/
#include <AT89X52.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int
//-------------adc0809�˿ڶ���--------------------
#define CHOOSE0809()  {P2_5=0;P2_6=1;P2_7=1;} //����0809Ƭѡ��
#define PORT_ADC0809  P0                      //0809���ݶ˿�
//------------------------------------------------
/****************************************************
*�������ƣ�channelChoose(uchar channel)
*�������ܣ�0809ת��ͨ��ѡ��
*��ڲ�����channel,ͨ��ѡ��
*���ڲ���������ͨ���������� 
****************************************************/
uchar channelChoose(uchar channel)
{
  uchar temp;
  CHOOSE0809();
  XBYTE[channel-1] =0x00;  //ѡ��ͨ�����ȴ�ת��
  while(P3_3==1);  //�ȴ�ת��
  temp =P0;
  return temp;
}
void main()
{
  uchar temp;
  while(1)
  { 
    temp =channelChoose(0x01);  //��ȡͨ��1
  }
}