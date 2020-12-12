#include "reg51.h"
#include "stdio.h"
#include "led1602.h"
#define ADC_POWER     0x80
#define ADC_FLAG      0x10
#define ADC_START     0x08
#define ADC_SPEEDLL   0x00
#define ADC_SPEEDL    0x20
#define ADC_SPEEDH    0x40
#define ADC_SPEEDHH   0x60

sfr AUXR      =0x8E;
sfr ADC_CONTR =0xBC;
sfr ADC_RES   =0xBD;
sfr ADC_RESL  =0xBE;
sfr P1ASF     =0x9D;

unsigned char ch=4;
bit flag=1;
float voltage=0;
unsigned char tstr[5];
unsigned int tmp=0;
void adc_int() interrupt 5
{
	unsigned char i=0;
	ADC_CONTR &=!ADC_FLAG;
	tmp=(ADC_RES*4+ADC_RESL);
	voltage=(tmp*5.0)/1024;
	sprintf(tstr,"%1.4f",voltage);
	flag=1;
	ADC_CONTR=ADC_POWER |ADC_SPEEDLL | ADC_START | ch;
}

void main()
{
	unsigned int i;
	P0M0=0;
	P0M1=0;
  P2M0=0;
	P2M1=0;
	P1ASF=0xFF;
	ADC_RES=0;
	ADC_CONTR=ADC_POWER|ADC_SPEEDLL | ADC_START | ch;
	for(i=0;i<10000;i++);
	IE=0xA0;
	lcdwait();
	lcdinit();
	lcdshowstr(0,0,"Measured Voltage is");
	lcdshowstr(6,1,"V");
	while(1)
		{ 
			if(flag==1)
			{
				flag=0;
	      lcdshowstr(0,1,tstr);
			}
		}
}
