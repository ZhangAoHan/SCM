//#include "reg51.h"
#include <STC15F2K60S2.H>
#include "intrins.h"

void main()
{
  WKTCL=0xff;
  WKTCH=0x84;
	P0M0=P0M1=0;
  P0=0x00;
  //P47=0;  
  while(1)
	{	
		
    P0=~P0;
    //P47=!P47;
    PCON|=0x02; 
		 _nop_();
		 _nop_();

	}		
}
