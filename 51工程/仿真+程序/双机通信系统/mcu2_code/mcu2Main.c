#include  "target.h"
#include  "led.h"
const uchar code displayMode=0x00;          //��ʾģʽ�������ַ�����
uchar displayBuff[4]={'0','0','0','0'};     //�������ʾ������ 
static uchar uart_get_mode;                 //�ӻ�����������ݽ׶μ�¼
void main()
{
   usart0_initial();     //���ڳ�ʼ��
   init_led();			 //led��ʼ��
   uart_get_mode=0x00;	 //�ӻ��������ݴ���0�׶�
   sei();			     //���ж�
	while(1)
	{
      ledSweepDisplay(displayBuff,displayMode,0x04);  
	}
}
/*******�����жϳ���********************/
void usart0_get() interrupt 4
{
  uchar temp;
  uchar count,i;
  temp=SBUF;  
  /*******************************************
  *��һ�׶�,����У����
  ********************************************/
  if(uart_get_mode==0x00)  
  {
    if(temp==0xAA)
	{
	  send_char(0xBB);
	}
  }
 /*********************************************
 *�ڶ��׶ν������ݳ��� �����ڱ�ʵ��һ�δ�������Ϊ
 *1���ֽڣ��ʴ�ʱ�����ݳ���Ϊ����״̬��
 **********************************************/
  if(uart_get_mode==0x01) 
  {
	  count=temp;
	  send_char(0xBB);
  }
 /********************************************
 *�����׶ν�������
 *********************************************/
  if(uart_get_mode==0x02) 
  {
    for(i=0;i<3;i++)
	{
	  displayBuff[i]=displayBuff[i+1];
	}
    displayBuff[3]=temp+'0';
	
  }
  if(uart_get_mode<0x02)
    uart_get_mode++;
  else
    uart_get_mode=0x00;
  RI=0;
}