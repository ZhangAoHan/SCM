#include "Include.h"
#include "led.h"
#include "target.h"
#define machineAddress 0x01 //���ӻ���ַ���� 
uchar displayBuff[2];          //�ӻ���ʾ�����������ӻ�ֻ��һ����ʾ��
uchar getCharStep;
void main()
{
  usart0_init();
  led_init();
  displayBuff[0]=0x00;
  getCharStep=0x00;
  sei();
  while(1)
  {
    ledWrite(displayBuff[0]+'0',0x01,DIGITAL);
  }
}
void uart_get_char(void) interrupt 4 
{
  uchar temp;
  static count,i;
  temp=SBUF;
  RI=0;
  RB8=0;
  if(getCharStep==0x00)       //��һ�׶ν��մӻ���ַ
  {
    if(temp==machineAddress)  //��ַ���
	{
	  send_char(temp);	      //�ظ�����
	  SM2=0;      		      //����������ݽ׶�
	}
	else
	{
	  return;
	}
  }
  if(getCharStep==0x01)	      //�ڶ��׶ν������ݳ���
  {
    count=temp;
	send_char(temp);
	i=0x01;
  }
  if(getCharStep==0x02)		  //�����׶ν�������
  {
    if(i!=count)			  //��ʵ��ʵ��count=0x01,�˶γ���Ϊ��չ���ն������ʹ��
	{
	  displayBuff[i-0x01]=temp;
	  i++;
	}
	else					  //�����������
	{
	  SM2=1;				  //������ַλ����
	  displayBuff[i-0x01]=temp;
	}	 
  }
  if(getCharStep<0x02)
   getCharStep++; 
  else if(SM2==1)
   getCharStep=0x00;
}