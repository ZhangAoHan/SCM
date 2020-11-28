#define LED_GLOBAL 1
#include "led.h"
/****************************************************
*�������ƣ�led_init(void)
*�������ܣ�����ܳ�ʼ��
*������ڣ���
*�������ڣ���
****************************************************/
void led_init(void)
{
  LED=segLedCode[0];
  LED_CS1=CS_FORCE_VALUE;   //��������LED���ݿ��������
  delay_us(10);
  LED_CS1=~CS_FORCE_VALUE;  //���������ݶ˿����ݱ���
}	       
/***********************************************************
*�������ƣ�ledWrite(uchar c,uchar n,uchar mod)
*�������ܣ����n�������дmodģʽ������c
*������ڣ�cΪҪ��ʾ������,��ʾ����ʱ,�������Ӧ���������ַ�;
nΪҪ��ʾ������ܱ��;modΪҪ��ʾ��ģʽ
*�������ڣ���
*˵�������ڱ�ʵ��Ϊһ���������ʾ���ʵ��ú���ʱnӦӳ��Ϊ0x01
*************************************************************/             
void ledWrite(uchar c,uchar n,uchar mod)
{
  if(CHARACTER==mod)  //Ϊ�����ֶ���ʾ
    LED=c;
  else if(DIGITAL==mod)
         LED=segLedCode[c-'0'];
  if(n==0x01)
  {
    LED_CS1=CS_FORCE_VALUE;
	delay_us(10);
	LED_CS1=~CS_FORCE_VALUE;
  }
}
/****************************************************
*�������ƣ�delay_us(uint us)
*�������ܣ�΢�뼶��ʱ����
*������ڣ�us,��ʱ����
*�������ڣ���
****************************************************/               
void delay_us(uint us)
{
  uchar delayi;
  while(--us)
  {
	for(delayi=0;delayi<10;delayi++);
  } 
}