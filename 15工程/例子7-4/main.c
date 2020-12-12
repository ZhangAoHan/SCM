#include "reg51.h"
void wakeup() interrupt 0
{
}
void main()
{
  long int j;
	IT0=1;                        
	EX0=1;                        
	EA=1;  
  while(1)
	{		
    P0=0x00;
  //P47=0;
    for(j=0;j<222222;j++);
    PCON|=0x01;
  //  P46=1;
    P0=0xff;	
    for(j=0;j<222222;j++);  
	}		
}
