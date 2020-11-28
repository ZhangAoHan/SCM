#define TARGET_GLOBAL 1
#include "target.h"
uint  timer0Count;       //timer0�������
uint  pulseCount;        //�������
uint  pulseCountTemp;    //��������Ĵ� 
/*************************************************
*�������ƣ�timer0_init(void)
*�������ܣ�timer0��ʼ��
*������ڣ���
*�������ڣ���
*˵������ϵͳ��12Mhz����,��ʱ1ms
*************************************************/
void timer0_init(void)
{
  TMOD|=0x01;   //timer0������MODEL1,timer
  TH0=0xFC;
  TL0=0x18;
  ET0=1;        //timer0�ж�ʹ��
  IP=0x02;      //timer0���ȼ����
  TR0=1;		//timer0����
}
/*************************************************
*�������ƣ�int0_init(void)
*�������ܣ��ⲿ�ж�0��ʼ��
*������ڣ���
*�������ڣ���
*************************************************/
void int0_init(void) 
{
    EX0 = 1;	 //�ⲿ�ж�0ʹ��
    IT0 = 1;	 //init0�����ж�
}
void target_init(void)
{
  timer0_init();
  int0_init();
  timer0Count=0;
  pulseCount=0;
  pulseCountTemp=0;
}
void T0_overflow(void) interrupt 1	//timer0����ж�,��ʱ1ms
{
  TH0=0xFC;
  TL0=0x18;
  cli();
  //IE0=0;
  if(timer0Count<1000)
    timer0Count++;
  else
  {
    
    pulseCountTemp=pulseCount-pulseCount/(uint)36;	//Ƶ�ʼ���У׼
	pulseCount=0;
    timer0Count=0;
  } 
  sei();
}
void int0(void) interrupt 0	//int0�ж���ں���,ʵʱ�������Ƶ��
{
  pulseCount++;
}
/*********************************************
*�������ƣ�uint get_fre_number(void)
*�������ܣ�����Ƶ�ʣ�1~1000HZ
*********************************************/
uint get_fre_number(void)
{
  return pulseCountTemp;
}