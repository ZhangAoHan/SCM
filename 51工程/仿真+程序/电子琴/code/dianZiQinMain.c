/**********************************************
*实例名称：电子琴
*实例原理：本实例共有七个按键,当按不同的按键时
会发出七种不同的声音
*作者：kxm
*时间：09.06.13
**********************************************/
#include "Include.h"
#include "key.h"
#include "sound.h"
#define  SOUND_OUT  P2_0
#define  YES  1
#define  NO   0
uchar Th0Temp;
uchar Tl0Temp;
void timer0_init()
{
  TMOD|=0x01;  //timer0,MODEL1,timer
  TH0=0;
  TL0=0;
  ET0=1;       //定时器0中断使能
  TR0=0;       //定时器0默认不启动
}
/******************************************
*定时器0溢出中断入口
******************************************/
void T0_overflow(void) interrupt 1
{
  TH0=Th0Temp;
  TL0=Tl0Temp;
  SOUND_OUT=!SOUND_OUT;
}
void main()
{
  uchar keyValueRead;
  timer0_init();
  key_init();
  sound_init();
  sei();
  keyValueRead=get_key_value();
  if(keyValueRead!=KEY_NULL)
  {
    if(TR0==NO)
	{
	   switch(keyValueRead)
	   { case 0x01:
	      {
		    TH0=yin[0][1];
			TL0=yin[0][0];
			Th0Temp=yin[0][1];
			Tl0Temp=yin[0][0];
		    break;
		  }
	     case 0x02:
		  {
		    TH0=yin[1][1];
			TL0=yin[1][0];
			Th0Temp=yin[1][1];
			Tl0Temp=yin[1][0];
		    break;
		  }
		 case 0x04:
		  {
		  	TH0=yin[2][1];
			TL0=yin[2][0];
			Th0Temp=yin[2][1];
			Tl0Temp=yin[2][0];
		    break;
		  }
		 case 0x08:
		  {
		  	TH0=yin[3][1];
			TL0=yin[3][0];
			Th0Temp=yin[3][1];
			Tl0Temp=yin[3][0];
		    break;
		  }
		 case 0x10:
		  {
		  	TH0=yin[4][1];
			TL0=yin[4][0];
			Th0Temp=yin[4][1];
			Tl0Temp=yin[4][0];
		    break;
		  }
		 case 0x20:
		  {
		    TH0=yin[5][1];
			TL0=yin[5][0];
			Th0Temp=yin[5][1];
			Tl0Temp=yin[5][0];
		    break;
		  }
		 case 0x40:
		  {
		    TH0=yin[6][1];
			TL0=yin[6][0];
			Th0Temp=yin[6][1];
			Tl0Temp=yin[6][0];
		    break;
		  }
	     default:
		   break;
	   } 
	  TR0=YES;
	}
  }
  else
  {
    TR0=NO;
	TH0=0x00;
	TL0=0x00;
	Th0Temp=0x00;
	Tl0Temp=0x00;
  }

}