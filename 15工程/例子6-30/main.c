#include "stdio.h"
#include "reg51.h"
void main()
{
	 int i;
	 SCON= 0x52;                     
   TMOD = 0x20;   
   TCON = 0x69;    
   TH1 = 0xF3;
	for(i=0;i<100;i++)
	{
    if(i==50) continue;	
	  if(i==80) break;
	  printf("i=%d is performed\n",i);
   }
}