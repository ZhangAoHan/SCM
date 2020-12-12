#include "reg51.h"
#include "stdio.h"
#define OSC           18432000L
#define BAUD          9600
#define URMD          0
#define ADC_POWER     0x80
#define ADC_FLAG      0x10
#define ADC_START     0x08
#define ADC_SPEEDLL   0x00
#define ADC_SPEEDL    0x20
#define ADC_SPEEDH    0x40
#define ADC_SPEEDHH   0x60

sfr T2H       =0xD6;
sfr T2L       =0xD7;
sfr AUXR      =0x8E;
sfr ADC_CONTR =0xBC;
sfr ADC_RES   =0xBD;
sfr ADC_RESL  =0xBE;
sfr P1ASF     =0x9D;

unsigned char ch=4;
float voltage=0;
unsigned char tstr[5];
unsigned int tmp=0;
float old_voltage=0;
void SendData(unsigned char dat)
{
	while(!TI);
	TI=0;
	SBUF=dat;
}

void adc_int() interrupt 5
{
	unsigned char i=0;
	ADC_CONTR &=!ADC_FLAG;
	tmp=(ADC_RES*4+ADC_RESL);
	voltage=(tmp*5.0)/1024;
	sprintf(tstr,"%1.4f",voltage);
	if(voltage!=old_voltage)
	{
	  old_voltage=voltage;
		SendData('\r');
	  SendData('\n');
	   for(i=0;i<5;i++)
	     SendData(tstr[i]);
	}
	ADC_CONTR=ADC_POWER |ADC_SPEEDLL | ADC_START | ch;
}

void main()
{
	unsigned int i;
	SCON=0x5A;
	T2L=65536-OSC/4/BAUD;
	T2H=(65536-OSC/4/BAUD)>>8;
	AUXR=0x14;
	AUXR|=0x01;
	P1ASF=0xFF;
	ADC_RES=0;
	ADC_CONTR=ADC_POWER|ADC_SPEEDLL | ADC_START | ch;
	for(i=0;i<10000;i++);
	IE=0xA0;
	while(1);
}
