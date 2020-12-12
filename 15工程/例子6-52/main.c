#include "stdio.h"
#include "reg51.h"
#include "max.h"  

void main()
{
	int k,l;
	float m;
	 SCON= 0x52;
   TMOD = 0x20;
   TCON = 0x69;
   TH1 = 0xF3;
	 k=max(i,j);
	 l=min(i,j);
	 m=avg(i,j);
	 printf("max value =%d\n",k);
	 printf("min value =%d\n",l);
	 printf("avg value =%f\n",m);
}