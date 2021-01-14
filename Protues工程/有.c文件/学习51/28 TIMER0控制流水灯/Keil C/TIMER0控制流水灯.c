/************************************/
/*程序名:TIMER0控制流水灯			*/
/*作 者 :铁手一郎					*/
/*时 间 :2009.6.20					*/
/*Q  Q  :347999853					*/
/*信息共享							*/
/************************************/
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint  unsigned int
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
	   for(y=110;y>0;y--);
}
void ledliu()
{
		uint aa;
		delay(500);
		 aa=P1;
		 aa=_crol_(aa,1);
		 P1=aa;	
}
void main()
{	

	P1=0xfe;
	TMOD=01;
	TH0=-50000/256;
	TL0=-50000%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1);
}
/**************中断服务函数*******************/
void T0_time() interrupt 1
{
	uint i;
	TH0=-50000/256;
	TL0=-50000%256;
	i++;
	if(i=10)
	{
		ledliu();
		i=0;
	}
	
}
