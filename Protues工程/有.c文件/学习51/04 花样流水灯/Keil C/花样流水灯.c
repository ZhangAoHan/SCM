#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
	  for(y=110;y>0;y--);
}
void main()
{
	uint aa,p,i;
	while(1)
    {
			aa=0xfe;
			P1=aa;
			for(i=0;i<7;i++)
			{	
				delay(500);
				aa=aa<<1;
				P1=aa;
			}
			for(i=0;i<8;i++)
			{	
				delay(500);
				aa=aa>>1;
				P1=aa;
			}
			P1=0xff;
		    delay(50);
		    for(i=0;i<5;i++)
			{
				P1=0x00;
				delay(300);
				P1=0xff;
				delay(300);	
			}
			
	
			aa=0xfe;
			P1=aa;
			for(p=0;p<7;p++)
			{
				delay(500);
				aa=_crol_(aa,1);
				P1=aa;
			}
			aa=0x7f;
			P1=aa;
			for(p=0;p<8;p++)
			{
				delay(500);
				aa=_cror_(aa,1);
				P1=aa;
			}
		
			for(i=0;i<5;i++)
			{
				P1=0x00;
				delay(300);
				P1=0xff;
				delay(300);	
			 }
			
		
	}
}	
