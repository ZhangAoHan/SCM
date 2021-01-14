/************************************/
/*程序名:TIMER0控制交通灯			*/
/*作 者 :铁手一郎					*/
/*时 间 :2009.6.20					*/
/*Q  Q  :347999853					*/
/*信息共享							*/
/************************************/
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int 
uchar i;
static uchar second;
bit red,green,yellow,turnred;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,
					 0x6d,0x7d,0x07,0x7f,0x6f};
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
/***************显示子程序**********************/
void display(uchar sun)
{
	uchar shi,ge;
	ge=table[sun/10];
	shi=table[sun%10];

	P2=0xff;
	P0=ge;
	P2=0x01;
	delay(5);

	P2=0xff;
	P0=shi;
	P2=0x02;
	delay(5);

	P2=0xff;
	P0=ge;
	P2=0x04;
	delay(5);

	P2=0xff;
	P0=shi;
	P2=0x08;
	delay(5);

	P2=0xff;
	P0=ge;
	P2=0x10;
	delay(5);

	P2=0xff;
	P0=shi;
	P2=0x20;
	delay(5);

	P2=0xff;
	P0=ge;
	P2=0x40;
	delay(5);

	P2=0xff;
	P0=shi;
	P2=0x80;
	delay(5);
}
/*****************清零函数************************/
void crl(void)
{
	display(0);
}
void main()
{
	TMOD=01;
	TH0=-50000/256;
	TL0=-50000%256;
	EA=1;
	ET0=1;
	TR0=1;
	second=30;
	red=1;
	P1=0xf5;
	while(1)
	{
		
		display(second);
		
		
	}
}
uchar count;
/*****************中断服务函数*******************/
void T0_time() interrupt 1
{
	TH0=-50000/256;
	TL0=-50000%256;
	count++;
	if (count==20)
	    {
	    count=0;
	    second--;//秒减1
		if(second==0)
		   {  //这里添加定时到0的代码 ，可以是灯电路，继电器吸合等，或者执行一个程序
	       if(red)
		     {
			  red=0;yellow=1;
	          second=5;
			  P1=0xdb;//黄灯亮5秒
			 }
		   else if(yellow && !turnred)
		     {
			  yellow=0;green=1;
	          second=50;
			  P1=0xee;//绿灯亮50秒
			 }
		   else if(green)
		     {
			 yellow=1;green=0;
	         second=5;
			 P1=0xdb;//黄灯亮5秒
			 turnred=1;
			 }
	       else if(yellow && turnred)
		     {
		     red=1;yellow=0;
			 P1=0xf5;;//红灯亮60秒
	         second=30;
			 turnred=0;
			 }
	
		   }
		
    
    }
}
