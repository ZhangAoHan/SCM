#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define SCANPORT P1
sbit spk=P3^0;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,
					 0x6d,0x7d,0x07,0x7f,0x6f,
					 0x77,0x7c,0x39,0x5e,0x79,
					 0x71};
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
		case 11:P0=table[0];spk=1;break;							  //'7'
		case 12:P0=table[1];spk=1;break;							  //'8'
		case 13:P0=table[2];spk=1;break;
		case 14:P0=table[3];spk=1;break;
							  
		case 21:P0=table[4];spk=1;break;							  //'4'
		case 22:P0=table[5];spk=1;break;							  //'5'
		case 23:P0=table[6];spk=1;break;
		case 24:P0=table[7];spk=1;break;
						  
		case 31:P0=table[8];spk=1;break;							  //'1'
		case 32:P0=table[9];spk=1;break;							  //'2'
		case 33:P0=table[10];spk=1;break;
		case 34:P0=table[11];spk=1;break;

		case 41:P0=table[12];spk=1;break;				  //'3'
		case 42:P0=table[13];spk=1;break;
		case 43:P0=table[14];spk=1;break;						  //'0'
		case 44:P0=table[15];spk=1;break;							  //'+'

		default:break;
		}
}
void main()
{
	spk=0;
	P0=0;
	
	while(1)
	{
		vKeyProcess(ucKeyScan());
		spk=0;
	}
}
