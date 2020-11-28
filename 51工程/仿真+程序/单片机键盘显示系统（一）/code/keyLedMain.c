#include "Include.h"
#include "key.h"
#include "led.h"
void main()
{
  uchar dispCode[8]={'0','0','0','0','0','0','0','0'};
  uchar keyScan;
  uchar ledCodeAlter=0;   /*led alter count*/
  key_init();
  led_init();
   while(1)
   {
     ledSweepDisplay(dispCode,8);
	 keyScan=get_key_value();
	 if(keyScan>0&&keyScan<11)
	 {
	    if(ledCodeAlter>7)
		  ledCodeAlter=0;
		if(keyScan==10)
		   dispCode[ledCodeAlter++]='0';
		else
		   dispCode[ledCodeAlter++]=keyScan+'0';
		   
	 }
	   
   }
}