#define LED_GLOBAL 1
#include "led.h"
/*******************************************************************************************
*函数名称：delay_us(uint us)
*函数功能：实现微秒级的延时
*函数入口：us,延时函数循环后期数
*函数出口：无
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
*函数名称：led_init(void)
*函数功能：四位七段数码管显示初始化
*函数入口：无
*函数出口：无
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
*函数名称：ledWrite(uchar c,uchar n,uchar mod)
*函数功能：对一组数码管的某一位进行短暂显示
*函数入口：c,要显示的数据;n,显示一组数码管中的第n位;mod,c的数据形式
*函数出口：无
*说明：当mod==DIGITAL时,c为数字0~9的ANCII码形式，此时在n位数码管上显示想用数字
       当mod==CHARACTER,直接将c输出数据口
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
*函数名称：ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber)
*函数功能：循环在数码管上显示缓冲区中的数据
*函数入口：segCode,指向显示缓冲区中的指针;segCodeMod,0~7位为1或0标示1~8位数码管显示的数据的类型（DIGITAL或者CHARACTER);segNumber,代表要显示数码管的位数
*函数出口：无
*说明：本函数主要实现将显示缓冲区中的数据在数码管上显示出来
*******************************************************************************************/	   	  
void ledSweepDisplay(uchar *segCode,uchar segCodeMod,uchar segNumber)
{
   	uchar segCount;
	for(segCount=0;segCount<segNumber;segCount++)
	{
	   if(segCodeMod&0x01)	   /*1代表此处显示任意字符 */
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
