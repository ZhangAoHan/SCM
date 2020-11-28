#define TARGET_GLOABAL
#include "target.h"
#define TARGET_GLOBAL 1
#include "target.h"
/*********************************************
*�������ƣ�usart0_Initial(void)
*�������ܣ���ʼ������
*��ں�������
*���ں�������
*********************************************/
void usart0_init(void)
{
/************TH1=256-(K*oscFreq)/384*BaudRate************/
    SCON=0xF0;   //SM0=1;SM1=1;SM2=1;REN=1;MODER3
	TI=0;        //���ݷ���״̬����
	RI=0;		 //���ݽ���״̬����
	RB8=0; 
	PCON=0;		 //���ӱ�
	TH1=0xFD;	 //bode=9600
	TL1=0XFD;
	TMOD=0X20;	 //TIMER1 MODER2;
	ET1=0;		 //����timer1����ж�
	TR1=1;		 //����timer1
	ES=1;		 //ʹ�ܴ����ж�
}
/*********************************************
*�������ƣ�send_char(uchar txd) 
*�������ܣ����ڷ���һ���ַ�
*��ں�����Ҫ���͵�һ���ַ�txd
*���ں�������
*********************************************/
void send_char(uchar txd) 
{
   TI=0;
   ES=0;
   SBUF=txd;
   while(!TI);				// �������ݴ���
   TI=0;					// ������ݴ��ͱ�־
   ES=1;
}
/********************************************
*�������ƣ�send_str(uchar *str,uchar len)
*�������ܣ����ڷ���һ���ַ���
*��ں������ַ���ָ��*str���ַ�������len
*���ں�������
********************************************/
void send_str(uchar *str,uchar len)
{
  uchar i;
  for(i=0;i<len;i++)
   send_char(str[i]);
}