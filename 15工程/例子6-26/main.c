#include "stdio.h"
#include "reg51.h"
void main()
{
	int s=0,i=1;
	SCON= 0x52;                     
  TMOD = 0x20;   
  TCON = 0x69;    
  TH1 = 0xF3; 

	while(i<=100)
	{ 
		s+=i;
		i++;
	}
	 printf("1+2+3+...+100= %d\n",s);
}