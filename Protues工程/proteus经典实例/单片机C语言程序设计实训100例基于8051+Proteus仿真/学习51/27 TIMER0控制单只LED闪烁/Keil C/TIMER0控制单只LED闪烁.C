/************************************/
/*程序名:TIMER0控制单只LED闪烁		*/
/*作 者 :铁手一郎					*/
/*时 间 :2009.6.21					*/
/*Q  Q  :347999853					*/
/*信息共享							*/
/************************************/
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int 
sbit led=P1^0;
void main()
{
	TMOD=0x01;
	TH0=-50000/256;
	TL0=-50000%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1);
}
/*************中断服务函数***********/
void T0_time() interrupt 1//
{	
	uint i;
	TH0=-50000/256;
	TL0=-50000%256;
	i++;
	if(i==20)
	{
		led=~led;
		i=0;
	}
}
