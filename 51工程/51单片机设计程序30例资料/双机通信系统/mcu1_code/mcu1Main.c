/*****************˫��ͨ����������******************************
*˫��ͨ��Э���飺
1.��������0xAA;
2.�ӻ��ظ�0xBB;
3.���������ַ�����len;
4.�ӻ��ظ�0xBB;
5.���������ַ�����
*�汾��0.0.0
*���ߣ�yd
*ʱ�䣺09.06.07
***************************************************************/
#include "target.h"
#include "key.h"
void send_key_value(uchar keySend)
{
  uchar temp;
  send_char(0xAA);     //����˫������Э��ͷ�ֽ�
  delay_us(10);
  temp=get_char();	   //��ȡ�ӻ��ظ��ֽ�
  if(temp==0xBB)	   //�ж��Ƿ�Ϊ0xBB
  {
    send_char(0x01);   //���͵����ݳ���
	delay_us(10);
	temp=get_char();   //��ȡ�ӻ��ظ��ֽ�
	if(temp==0xBB)	   //�ж��Ƿ�Ϊ0xBB
	{
	  send_char(keySend);
	}
  }
}
void main()
{
	uchar c=0;
	uchar keyValueRead;
	usart0_initial();
	init_key();
	while(1)
		{
		   keyValueRead=get_key_value();  //��ȡ���µİ���
		   if(keyValueRead!=KEY_NULL)
		   {
		     if(keyValueRead==KEY_ONE)
			   c=0x01;
			 if(keyValueRead==KEY_TWO)
			   c=0x02;
			 if(keyValueRead==KEY_THREE)
			   c=0x03;
			 if(keyValueRead==KEY_FOUR)
			   c=0x04;
			 send_key_value(c);
		   }
		 }	   
}

