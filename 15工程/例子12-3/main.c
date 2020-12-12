#include "reg51.h"
#include "stdio.h"
#include "12864.h"
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
unsigned char max_tstr[10],min_tstr[10],avg_tstr[10];
unsigned int tmp=0;
xdata unsigned char value[128];
unsigned int max_value=0 ,min_value=1024,avg_value=10;
unsigned char inc=0;
void adc_int() interrupt 5
{
	unsigned char i=0;
	ADC_CONTR &=!ADC_FLAG;
	tmp=(ADC_RES*4+ADC_RESL);
  if(inc!=128 && flag==0)
	{
	  	value[inc]=tmp/16;
	  	if(tmp>max_value)
			      max_value=tmp;
		  if(tmp<min_value)
			     min_value=tmp;
		   inc++;
	}
	else
	{
		    inc=0;
		    flag=1;
	}
	ADC_CONTR=ADC_POWER |ADC_SPEEDLL | ADC_START | ch;
}

void main()
{
	long unsigned int i;
	P0M0=0;
	P0M1=0;
  P2M0=0;
	P2M1=0;
	P1ASF=0xFF;
	ADC_RES=0;
	ADC_CONTR=ADC_POWER|ADC_SPEEDLL | ADC_START | ch;
	for(i=0;i<10000;i++);
	IE=0xA0;
  lcdinit();
	lcdshowstr(0,0,"测量交流信号");
	for(i=0;i<600000;i++);
	lcdwritecmd(0x01);
		while(1)
		{ 
		if(flag==1)
			{
				  lcdinit();
				  sprintf(max_tstr,"%+1.4f",(max_value*5.0)/1024);
		      sprintf(min_tstr,"%+1.4f",(min_value*5.0)/1024);
				  sprintf(avg_tstr,"%+1.4f",((max_value-min_value)*5.0)/1024);
				  max_value=0;
		      min_value=1024;
				  lcdshowstr(0,1,"MAX: ");
	        lcdshowstr(2,1,max_tstr);
				  lcdshowstr(5,1," V");
				  lcdshowstr(0,2,"MIN: ");
	        lcdshowstr(2,2,min_tstr);
				  lcdshowstr(5,2," V");
				  lcdshowstr(0,3,"PTP: ");
				  lcdshowstr(2,3,avg_tstr);
				  lcdshowstr(5,3," V");
				for(i=0;i<300000;i++);
      	lcdwritecmd(0x01);
        drawpoint(value); 
				flag=0;	
			} 
		}
}
