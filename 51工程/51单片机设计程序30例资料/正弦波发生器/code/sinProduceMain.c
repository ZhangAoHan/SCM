#include "sin.h"
double  sinInterTime;
void main()
{
  sinInterTime=(1000UL)/(SIN_FRE*SIN_SEG);     //�������Ҳ�Ƶ�ʼ��㶨ʱ��0��ʱʱ��
  timer0_init(sinInterTime);				   //��ʼ����ʱ��0
  dac0832_init();                          	   //dac0832��ʼ��
  sei();
  while(1);
}
/***************************************************
*�������ƣ�Timer0_Sin(void)
*�������ܣ�timer0�ж����,��ʱ�����������
*������ڣ���
*�������ڣ���
****************************************************/
void Timer0_Sin(void) interrupt 1
{											
   TH0=timer0TH0;        //������д��
   TL0=timer0TL0;
    
   if(sinCodeCount<128)
    {
	  writeDAC0832(Sin[sinCodeCount]);
	  sinCodeCount+=SIN_SPACING; 
	}
	else
	{
	  sinCodeCount=0;
	  writeDAC0832(Sin[sinCodeCount]);
	}
	sei();
       
}