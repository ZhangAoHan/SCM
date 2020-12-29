#define LED_GLOBAL 1
#include "led.h"
extern void delay(uint us);     //�����ӳٺ�����ʵ������key.c�ļ��� 
extern void delay_us(uint us); 
/******************************************************************************
* ��������:
* ��    ��:
* ��ڲ���:
* ���ڲ���:
********************************************************************************/
void init_led(void)
{
   LED=segLedCode[0];
   LED_CS1=0;
   LED_CS2=0;
   LED_CS3=0;
   LED_CS4=0;
}	  
/******************************************************************************
* ��������:
* ��    ��:
* ��ڲ���:
* ���ڲ���:
********************************************************************************/
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
/******************************************************************************
* ��������:
* ��    ��:
* ��ڲ���:
* ���ڲ���:
********************************************************************************/
	   	  
void ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber) 
{											//ѭ����ʾ�Ӻ���
   	uchar segCount;
	for(segCount=0;segCount<segNumber;segCount++)
	{
	   if(segCodeMod&0x01)	               //1����˴���ʾ�����ַ�
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
