#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define SCANPORT P1
uchar uca_LineScan[4]={0xEF,0xDF,0xBF,0x7F};
uchar ucKeyScan()
{
	uchar Temp=0;			  	
	uchar ucRow=0,ucLine=0;	    

	for(ucLine=0;ucLine<4;ucLine++)	
		{
			SCANPORT=uca_LineScan[ucLine];			   
			Temp=SCANPORT & 0x0F;					 
			if(Temp!=0x0F)		 
				{									 
				switch(Temp)
					{
					case 0x0E: ucRow=10;break;		 
					case 0x0D: ucRow=20;break;
					case 0x0B: ucRow=30;break;
					case 0x07: ucRow=40;break;
					default:   ucRow=50;break;
					}
				break;
				}
		}

	SCANPORT=0x0F;	  				
	return ucRow+ucLine+1;			 
}
void vKeyProcess(unsigned char ucKeyCode)
{
		
	switch(ucKeyCode)
		{
		case 11:P2=0xff;P3=0x7f;break;							  //'7'
		case 12:P2=0xff;P3=0x3f;break;							  //'8'
		case 13:P2=0xff;P3=0x1f;break;
		case 14:P2=0xff;P3=0x0f;break;
							  
		case 21:P2=0xff;P3=0x07;break;							  //'4'
		case 22:P2=0xff;P3=0x03;break;							  //'5'
		case 23:P2=0xff;P3=0x01;break;
		case 24:P2=0xff;P3=0x00;break;
						  
		case 31:P3=0x00;P2=0x7f;break;							  //'1'
		case 32:P3=0x00;P2=0x3f;break;							  //'2'
		case 33:P3=0x00;P2=0x1f;break;
		case 34:P3=0x00;P2=0x0f;break;

		case 41:P3=0x00;P2=0x07;break;				  //'3'
		case 42:P3=0x00;P2=0x03;break;
		case 43:P3=0x00;P2=0x01;break;						  //'0'
		case 44:P3=0x00;P2=0x00;break;							  //'+'

		default:break;
		}
}
void main()
{
	while(1)
	{
		vKeyProcess(ucKeyScan());
	}
}
