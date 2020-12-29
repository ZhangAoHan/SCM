#include "led.h"
#include "TLC2543.h"
const uchar code displayMode=0x0f;
uchar displayBuff[4]={0x7e,0x7e,0x7e,0x7e};   //数码管显示缓冲区，低两位为时间，最高位为抢答号
const uchar code digitalNumber[10]={0x7e,0x06,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x73};
void main()
{	 
  uint voltageReadTemp;
  uint voltageRead;
  uchar temp;
  uchar i,j;
  init_led();
  while(1)
  {
    ledSweepDisplay(displayBuff,displayMode,4);
    voltageRead=read_TLC2543(0x05);
	voltageRead=voltageRead*0x05;
	for(i=4;i>0;i--)
	{
	  temp=(uchar)(voltageRead/0x0fff);
	  if(i==4)
	    displayBuff[i-1]=digitalNumber[temp]|0x80;
	  else
	    displayBuff[i-1]=digitalNumber[temp]; 
	  voltageRead=voltageRead%0x0fff;
	  voltageReadTemp=voltageRead<<1;
	  voltageRead=0x0000;
	  for(j=0;j<5;j++)
	    voltageRead+=voltageReadTemp;//voltageRead=voltageRead*10
	   
	}

  }
 
}