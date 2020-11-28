#define LED_GLOBAL 1
#include "led.h"
extern void delay_us(uint us);                   /*����΢�뼶��ʱ����*/
/****************************************************
*�������ƣ�led_init(void)
*�������ܣ�����ܳ�ʼ��
*������ڣ���
*�������ڣ���
****************************************************/
void led_init(void)
{
  //�������ʾpwm��ʼ��ֵ��1/100
  ledWrite('1',0x01,DIGITAL);  
  ledWrite('0',0x02,DIGITAL);
  ledWrite('0',0x03,DIGITAL);
}	       
/***********************************************************
*�������ƣ�ledWrite(uchar c,uchar n,uchar mod)
*�������ܣ����n�������дmodģʽ������c
*������ڣ�cΪҪ��ʾ������,��ʾ����ʱ,�������Ӧ���������ַ�;
nΪҪ��ʾ������ܱ��;modΪҪ��ʾ��ģʽ
*�������ڣ���
*************************************************************/             
void ledWrite(uchar c,uchar n,uchar mod)
{
  if(CHARACTER==mod)  //Ϊ�����ֶ���ʾ
    LED=c;
  else if(DIGITAL==mod)
         LED=segLedCode[c-'0'];
   switch(n)
   {
     case 0x01:
	  {
	    LED_CS1=CS_FORCE_VALUE;
	    delay_us(10);
	    LED_CS1=0;    //~CS_FORCE_VALUE
		break;
	  }
	 case 0x02:
	  {
	   	LED_CS2=CS_FORCE_VALUE;
	    delay_us(10);
	    LED_CS2=0;
		break;
	  }
	 case 0x03:
	  {
	    LED_CS3=CS_FORCE_VALUE;
	    delay_us(10);
	    LED_CS3=0;
		break;
	  }
	 default:
	   break;
   }
}