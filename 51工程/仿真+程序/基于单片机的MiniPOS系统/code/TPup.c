#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char

sbit BUSY=P2^6;
sbit STB=P2^7;

void topin(uchar *p) 
{
	while(*p!='\0')
		{
			while(BUSY!=0); //��ѯ��ӡ��״̬
			P0=*p;          //����ַ�
			STB=0;          //ģ��STB����
      p++;
		}
}

void main()
{
  uchar idata prn[]="welcome";  //��ӡ welcome �ַ���
	toprn(prn); 
}
	                    
	                     