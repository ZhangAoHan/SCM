#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit RED_A=P0^0;
sbit YELLOW_A=P0^1;
sbit GREEN_A=P0^2;
sbit RED_B=P0^3;
sbit YELLOW_B=P0^4;
sbit GREEN_B=P0^5;

uchar Flash_Count = 0;
Operation_Type = 1;

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	{
	 	for(t=120;t>0;t--);
	}
}

void Traffic_lignt()
{
 	switch(Operation_Type)
	{
	 	case 1:
			RED_A=1;YELLOW_A=1;GREEN_A=0;
			RED_B=0;YELLOW_B=1;GREEN_B=1;
			DelayMS(2000);
			Operation_Type = 2;
			break;
		case 2:
			DelayMS(200);
			YELLOW_A=~YELLOW_A;
			if(++Flash_Count !=10) 
				return;
			Flash_Count=0;
			Operation_Type = 3;
			break;
		case 3:
			RED_A=0;YELLOW_A=1;GREEN_A=1;
			RED_B=1;YELLOW_B=1;GREEN_B=0;
			DelayMS(2000);
			Operation_Type = 4;
			break;	
		case 4:
			DelayMS(200);
			YELLOW_B=~YELLOW_B;
			if(++Flash_Count !=10) 
				return;
			Flash_Count=0;
			Operation_Type = 1;
			break;	
	}
}

void main()
{
 	while(1)
	{
	 	Traffic_lignt();	
	}
}
