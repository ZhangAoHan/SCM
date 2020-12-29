/******************************************************
*�ļ����ƣ�ledMain.c
*�ļ����ܣ�led��ʾ����
*�汾��	   V0.0.0
*���ߣ�	   yd
*ʱ�䣺	   09.07.22
*˵����led����Ʒ�ʽ��ʾ�����ݿ�ͨ��8255��չ
******************************************************/
#include <AT89X51.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int
#define sei() (EA=1)	//�����ж�
#define cli() (EA=0)	//�����ж�
enum PORT8255 { PA8255 =0x01,PB8255 =0x02,PC8255 =0x03};  //8255�����˿�ģʽѡ��
#define  PORT8255  P0									  //8255���ݶ˿�
#define  CS8255()  {P2_5 =0;P2_6 =1;P2_7 =0;}   	      //Ƭѡ8255   
#define  PAADDRESS  0x00                    		      //8255PA�ڲ�����ַ
#define  PBADDRESS  0x01							      //8255PB�ڲ�����ַ
#define  PCADDRESS  0x02							      //8255PC�ڲ�����ַ
#define  CONADDRESS 0x03                    		      //8255���ƼĴ�����ַ
uchar  loopVar;          //ѭ������
uchar  timer0Count;	     //��ʱ��0����ж�
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
/**************************************
*�������ƣ�timer0Init(void)
*�������ܣ���ʱ��0��ʼ��,��ʱ10ms
*��ڲ�������
*���ڲ�������
**************************************/
void timer0Init(void)
{
   TMOD |= 0x01;                        //GATE=0,TR=1����;C/T=1,counter,0,timer;01ʮ������  
   TH0 = 0xdc;
   TL0 = 0x00;
   TR0 = 1;	                            //timer0 ����λ��Ϊ1ʱ����timer0
   ET0 = 1;                             //timer0 �ж�ʹ�� 
}
void main()
{
  timer0Init();	             //��ʱ��0��ʼ������ʱ10ms
  loopVar=0xfe;
  timer0Count=0x00;
  write8255(PA8255,loopVar); //ͨ��8255�����led��ʾ
  sei();
  while(1);
}
/********************************************************************************************
* �������ƣ���ʱ��0�жϺ���
* ��    �ܣ���ʱ��0����ж���ڴ�,��ʱ10ms
* ��ڲ�������
* ���ڲ�������
*********************************************************************************************/
void timer0_overflow(void) interrupt 1 
{
   TH0 = 0xdc;
   TL0 = 0x00;
   if(timer0Count<50)   //��ʱ0.5��
     timer0Count++;
   else
   {
     timer0Count =0x00;
	 if(loopVar&0x80)	            //�Ƿ��Ƶ����λ
	 {
	   	loopVar =loopVar <<1;
	    loopVar =loopVar &0x01;
	 }
	 else
	 {
	   	loopVar=0xfe;
	 }
	 write8255( PA8255,loopVar);    //�����ѭ����λ��ʾ
   }
   sei();
}