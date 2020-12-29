/*****************************************************
* �ļ����ƣ�CSB.c							   
* ���ܣ����������
* ��ǰ�汾��1.0
* ���ߣ�YuanDong
* ������ڣ�2009��7��18��
******************************************************/
#include <reg52.h>
#include "intrins.h"
#include "12864LCDdriver.h"
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long int
#define V=173
sbit CSOut=P1^7;
sbit Start=P1^4;

ulong TIME;
uchar DISTANCE;
uchar code discode[11]={'0','1','2','3','4','5','6','7','8','9',' '};
ulong data disnum[5];
bit data ReceiveOK=0;
bit data TOut;
bit data FLAG;
 
/*********************************************************
* �������ƣ�void delay2(uchar x)
* ��    �ܣ���ʱ����
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void delay2(uchar x)
{
 uchar a,b;
 for(a=0;a<x;a++)
  for(b=0;b<255;b++);
}
 
/*********************************************************
* �������ƣ�void init(void)
* ��    �ܣ���ʼ��
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void init(void)
{
 lcd_init();//LCD��ʼ������������һ��
 TMOD=0x01;//T0��ʱ����ʽ1
 IT0=0;//INT0�����ش���
 IP=0x01;//INT0�����ȼ�
 EA=1;//�����ж�
}
  
/*********************************************************
* �������ƣ�
* ��    �ܣ����������亯��
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void CCOut(void)
{
 TR0=1;
//40KHz
 CSOut=0;//1
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//2
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//3
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//4
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//5
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//6
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//7
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//8
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//9
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//10
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();
 CSOut=0;//11
 _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();
 CSOut=1;//12
}
  
/*********************************************************
* �������ƣ�void DataProcess(void)
* ��    �ܣ����ݴ�����
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void DataProcess(void)
{
  ulong time=0;
  TIME=TH0;
  TIME=(TIME<<8)|TL0;
  TIME*=173;//����
  TIME=TIME/10000;//��λ:CM
  disnum[0]=(uchar)TIME%10;        //��λ
  disnum[4]=TIME/10;
  disnum[1]=(uchar)disnum[4]%10;//ʮλ
  disnum[4]=disnum[4]/10;
  disnum[2]=(uchar)disnum[4]%10;//��λ
  disnum[4]=disnum[4]/10;
  disnum[3]=(uchar)disnum[4]%10;//ǧλ
}
/*********************************************************
* �������ƣ�void TimeOut(void) interrupt 1
* ��    �ܣ���ʱ������ T0
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void TimeOut(void) interrupt 1
{
 TR0=0;
 ET0=0;
 EX0=0;
 ReceiveOK=0;
 TOut=1;
}
	 
/*********************************************************
* �������ƣ�void Receive(void) interrupt 0
* ��    �ܣ����������մ�����
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void Receive(void) interrupt 2
{
 TR0=0;
 EX0=0;
 ET0=0;
 ReceiveOK=1; //�趨���ճɹ���־
 TOut=0;      //�����ʱ��־
}
   
/*********************************************************
* �������ƣ�void LCDDisplay(void)
* ��    �ܣ����������ʾ����
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void LCDDisplay(void)
{
 lcd_home();
 lcd_writestr(0,0,"  �����������  ");
 lcd_writestr(1,0,"����������������");
 lcd_writestr(2,0,"��ǰ�������Ϊ��");
 lcd_writestr(3,0,"        ����    ");
 lcd_writechar(discode[disnum[3]],discode[disnum[2]],discode[disnum[1]],discode[disnum[0]]);
}

/*********************************************************
* �������ƣ�void ErrorDisplay(void)
* ��    �ܣ�������ʾ����
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void ErrorDisplay(void)
{
 lcd_home();
 lcd_writestr(0,0,"  �����������  ");
 lcd_writestr(1,0,"����������������");
 lcd_writestr(2,0,"δ�յ��ز��źţ�");
 lcd_writestr(3,0,"�����̲������룡");
}
	 
/*********************************************************
* �������ƣ�void ReadyDis(void)
* ��    �ܣ�Ԥ������ʾ����
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void ReadyDis(void)
{
 lcd_home();
 lcd_writestr(0,0,"  �����������  ");
 lcd_writestr(1,0,"����������������");
 lcd_writestr(2,0,"    ��׼����    ");
 lcd_writestr(3,0,"    �ȴ�����    ");
}
	
/*********************************************************
* �������ƣ�void main(void)
* ��    �ܣ�������
* ��ڲ�������
* ���ڲ�������
*********************************************************/
void main(void)
{
  uchar ct;
  init();         //��ʼ��
  ReadyDis();
  while(1)
  {
    if(Start==0)
    {
      delay2(50);
      if(Start==0) FLAG=1;
    } 
 
    if(FLAG==1)   //��������һ��
    {
      TH0=0x00;
      TL0=0x00;
      TIME=0x00;
      ET0=1;
      CCOut();
      ct=100;
      while(--ct);
      EX0=1;
      while(TOut==0)
      {
        if(ReceiveOK==1)    //���ճɹ�
        {
           DataProcess();   //���ݴ���
           LCDDisplay();    //LCD��ʾ
           ReceiveOK=0;     //������ճɹ���־
           goto aa;
        }
      }
      if(TOut==1)
      {
        TOut=0;
        ErrorDisplay(); //��ʱ,������ʾ
      }
  aa: FLAG=0;            //�����ʱ��־,�ȴ���һ�β���
    }
  }
}
 
