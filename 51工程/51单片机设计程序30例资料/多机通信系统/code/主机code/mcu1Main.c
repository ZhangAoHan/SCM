//**************************************************************
/*****************˫��ͨ����������******************************
*˫��ͨ��Э���飺
1.�������ʹӻ���ַ,����0x01;
2.�ӻ��ظ���ַ����0x01;
3.���������ַ�����len;
4.�ӻ��ظ�len;
5.���������ַ�����
*�汾��0.0.1
*���ߣ�kxm
*ʱ�䣺09.06.10
***************************************************************/
//**************************************************************
#include "target.h"
#include "key.h"
#define REG_MAX 10        //���������ֵ
uchar sendBuff[REG_MAX];  //���ڻ�����
/********************************************************
*�������ƣ�send_data_package(uchar address,uchar sendLen)
*�������ܣ���ӻ�����һ�����ݰ�
*������ڣ��ӻ���ַaddress,�������ݳ���sendLen
*�������ڣ���
*˵�����������ݰ�����ʱ��Ӧ�����ݷŻ�������
*********************************************************/
void send_data_package(uchar address,uchar sendLen)
{
  uchar temp;
  uchar i;
  TB8=1;                //���͵�ַ���� 
  send_char(address);
  delay_us(10);
  temp=get_char();     //��ȡ�ӻ���ַ���ݻظ�
  if(temp!=address)    //���ظ��ͷ��Ͳ�ͬ����������
    return;
  TB8=0;               //�������ݳ���
  send_char(sendLen);
  delay_us(10);
  temp=get_char();
  if(temp!=sendLen)
    return;
  for(i=0;i<sendLen;i++)
    send_char(sendBuff[i]);
}
void main()
{
	uchar keyValueRead;
	uchar keyReg[2]={0x00,0x00};
	uchar c;
	usart0_initial();	  //���ڳ�ʼ��
	init_key();			  //������ʼ��
	while(1)
		{
		   keyValueRead=get_key_value();
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
			 if(keyValueRead==KEY_FIVE)
			   c=0x05;
			 keyReg[1]=keyReg[0];
			 keyReg[0]=c;
			 sendBuff[0]=keyReg[0];	       //�����͸���ַΪ0x02�Ĵӻ������ݷ��뷢�ͻ���
			 send_data_package(0x02,0x01); //�����������ݷ���0x02�ӻ�
			 sendBuff[0]=keyReg[1];		   //�����͸���ַΪ0x01�Ĵӻ������ݷ��뷢�ͻ���
			 send_data_package(0x01,0x01); //�����������ݷ���0x01�ӻ�
		   }
		 }	   
}

