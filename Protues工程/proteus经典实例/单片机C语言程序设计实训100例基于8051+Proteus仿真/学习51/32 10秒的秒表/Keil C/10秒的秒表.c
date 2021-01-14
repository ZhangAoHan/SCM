/************************************/
/*������:10������		            */
/*�� �� :����һ��					*/
/*ʱ �� :2009.6.21					*/
/*Q  Q  :347999853					*/
/*��Ϣ����							*/
/************************************/
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit s1=P3^0;
uchar sun; 
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,
					 0x6d,0x7d,0x07,0x7f,0x6f};
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
/***************��ʾ�ӳ���************************/
void display(uchar sum)
{
	uchar ge,shi;
	ge=table[sum%10];
	shi=table[sum/10];
	
	P2=1;
	P0=ge;
	P2=0xfe;
	delay(5);

	P2=1;
	P0=shi;
	P2=0xfd;
	delay(5);	
}
/**************����ɨ�躯��**********************/
void keycan()
{
	uint i;
	if(s1==0)
	{
		delay(30);
		if(s1==0)
		{
			i++;
			switch(i)
			{
				case 1:TR0=0;break;
				case 2:sun=0;break;
				case 3:TR0=1;i=0;break;
				default:break;
			}
			while(!s1);
		}
	}
}
void main()
{
	
	TMOD=01;
	TH0=-50000/256;
	TL0=-50000%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1)
	{
		display(sun);
		keycan();
	}
}
/***************�жϷ�����**********************/
void T0_time() interrupt 1
{	
	uint i;
	TH0=-50000/256;
	TL0=-50000%256;
	i++;
	if(i==20)
	{
		i=0;
		sun++;
		if(sun==11)
		{
			sun=0;
		}
	}
}
