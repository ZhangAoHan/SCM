#define LED_GLOBAL 1
#include "led.h"
/*******************************************************************************************
*�������ƣ�delay_us(uint us)
*�������ܣ�ʵ��΢�뼶����ʱ
*������ڣ�us,��ʱ����ѭ��������
*�������ڣ���
*******************************************************************************************/
void delay_us(uint us)
{
  uint i;
  while(us--)
  {
    for(i=0;i<100;i++);
  }
}
/*******************************************************************************************
*�������ƣ�led_init(void)
*�������ܣ���λ�߶��������ʾ��ʼ��
*������ڣ���
*�������ڣ���
*******************************************************************************************/
void init_led(void)
{
   LED=segLedCode[0];
   LED_CS1=0;
   LED_CS2=0;
   LED_CS3=0;
   LED_CS4=0;
}
/*******************************************************************************************
*�������ƣ�ledWrite(uchar c,uchar n,uchar mod)
*�������ܣ���һ������ܵ�ĳһλ���ж�����ʾ
*������ڣ�c,Ҫ��ʾ������;n,��ʾһ��������еĵ�nλ;mod,c��������ʽ
*�������ڣ���
*˵������mod==DIGITALʱ,cΪ����0~9��ANCII����ʽ����ʱ��nλ���������ʾ��������
       ��mod==CHARACTER,ֱ�ӽ�c������ݿ�
*******************************************************************************************/
void ledWrite(uchar c,uchar n,uchar mod)
{
   if(CHARACTER==mod)
   {
	  LED=c;  
   }
   else if(DIGITAL==mod)
	   {
	      if((c-'0')<0x0a)
		  {
		    LED=segLedCode[c-'0'];
		  } 
		  else
		  {  
			LED=segLedCode[0];
		  }
	   }
   switch(n)
   {
		case 0x01:
		{
		  LED_CS1=0;
		  delay_us(10);
		  LED_CS1=1;
		  break;
		}
		case 0x02:
		{
		  LED_CS2=0;
		  delay_us(10);
		  LED_CS2=1;
		  break;
		}
		case 0x03:
		{
		  LED_CS3=0;
		  delay_us(10);
		  LED_CS3=1;
		  break;
		}
	    case 0x04:
		{
		  LED_CS4=0;
		  delay_us(10);
		  LED_CS4=1; 
		  break;
		}
		default:
		  break;

   }

}
/*******************************************************************************************
*�������ƣ�ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber)
*�������ܣ�ѭ�������������ʾ�������е�����
*������ڣ�segCode,ָ����ʾ�������е�ָ��;segCodeMod,0~7λΪ1��0��ʾ1~8λ�������ʾ�����ݵ����ͣ�DIGITAL����CHARACTER);segNumber,����Ҫ��ʾ����ܵ�λ��
*�������ڣ���
*˵������������Ҫʵ�ֽ���ʾ�������е����������������ʾ����
*******************************************************************************************/	   	  
void ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber)
{
   	uchar segCount;
	for(segCount=0;segCount<segNumber;segCount++)
	{
	   if(segCodeMod&0x01)	   /*1����˴���ʾ�����ַ� */
	   {
	     ledWrite(segCode[segCount],segCount+1,CHARACTER); 
	   }
	   else
	   {
	     ledWrite(segCode[segCount],segCount+1,DIGITAL);
	   }
	   segCodeMod=segCodeMod>>1;
	}
}
