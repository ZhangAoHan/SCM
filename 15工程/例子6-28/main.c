#include "stdio.h"
#include "reg51.h"
void main()
{
	int i=0,n=1;
	float p=1;
	float t=1.0;
	SCON= 0x52;                     
  TMOD = 0x20;   
  TCON = 0x69;    
  TH1 = 0xF3; 
for(i=1;i<64;i++)
	{
		p=p*2;
		t+=p;
	}
	 printf("sum = %f\n",t);
   printf("sum = %e\n",t);	
}
