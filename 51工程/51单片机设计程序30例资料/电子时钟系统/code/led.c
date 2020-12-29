#define LED_GLOBAL 1
#include "led.h"
extern void delay(uint us);     //�����ӳٺ�����ʵ������key.c�ļ��� 
extern void delay_us(uint us); 
/********************************************************************************************
* �������ƣ�void init_led(void)
* ��    �ܣ�led������ʼ��
* ��ڲ�������
* ���ڲ�������
*********************************************************************************************/
void init_led(void)
{
   LED = segLedCode[0];
   LED_CS1 = 0;
   LED_CS2 = 0;
   LED_CS3 = 0;
   LED_CS4 = 0;
   LED_CS5 = 0;
   LED_CS6 = 0;
   LED_CS7 = 0;
   LED_CS8 = 0;
}				   
/********************************************************************************************
* �������ƣ�void ledWrite(uchar c,uchar n,uchar mod)
* ��    �ܣ�ledд�ַ�����
* ��ڲ�����uchar c,uchar n,uchar mod
* ���ڲ�������
*********************************************************************************************/
void ledWrite(uchar c,uchar n,uchar mod)
{
   if(CHARACTER == mod)
	  LED = c; 
   else if(DIGITAL == mod)
	   {
	      if((c - '0') < 0x0a)
		  {
		    LED = segLedCode[c - '0'];
		  } 
		  else
		  {  
			LED = segLedCode[0];
		  }
	   }
   switch(n)				//�����Ƭѡ
   {
		case 0x01:
		{
		  LED_CS1 = 0;
		  delay_us(10);
		  LED_CS1 = 1;
		  break;
		}
		case 0x02:
		{
		  LED_CS2 = 0;
		  delay_us(10);
		  LED_CS2 = 1;
		  break;
		}
		case 0x03:
		{
		  LED_CS3 = 0;
		  delay_us(10);
		  LED_CS3 = 1;
		  break;
		}
	    case 0x04:
		{
		  LED_CS4 = 0;
		  delay_us(10);
		  LED_CS4 = 1; 
		  break;
		}
		case 0x05:
		{
		  LED_CS5 = 0;
		  delay_us(10);
		  LED_CS5 = 1;
		  break;
		}
		case 0x06:
		{
		  LED_CS6 = 0;
		  delay_us(10);
		  LED_CS6 = 1;
		  break;
		}
		case 0x07:
		{
		  LED_CS7 = 0;
		  delay_us(10);
		  LED_CS7 = 1;
		  break;
		}
		case 0x08:
		{
		  LED_CS8 = 0;
		  delay_us(10);
		  LED_CS8 = 1;
		  break;
		}
		default:
		  break;

   }

}

/********************************************************************************************
* �������ƣ�void ledSweepDisplay(uchar *segCode,uchar segCodeMod)
* ��    �ܣ���ʾ�Ӻ���
* ��ڲ�����*segCode��segCodeMod
* ���ڲ�������
*********************************************************************************************/	   	  
void ledSweepDisplay(uchar *segCode,uchar segCodeMod)	    //ѭ����ʾ�Ӻ��� 
{
   	uchar segCount;
	for(segCount = 0;segCount < 8;segCount++)
	{
	   if(segCodeMod&0x01)	                                //1����˴���ʾ�����ַ� 
	   {
	     ledWrite(segCode[segCount],segCount + 1,CHARACTER); 				   
	   }
	   else
	   {
	     ledWrite(segCode[segCount],segCount + 1,DIGITAL);
	   }
	   segCodeMod = segCodeMod >> 1;
	}
}
