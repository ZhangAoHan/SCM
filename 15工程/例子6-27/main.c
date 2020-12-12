#include "stdio.h"
#include "reg51.h"
void main()
{
	int i=0,n;
	long int p=1;
	SCON= 0x52;                     
  TMOD = 0x20;   
  TCON = 0x69;    
  TH1 = 0xF3; 
  printf("the following will calculate 2**n\n");
  printf("please input n value(1~16)\n");
do{
	i=0;
	p=1;
	scanf("%d",&n);
  do
   	{ 
		  p=2*p;
		  i++;
	  }
		while(i<n);
	 printf("2**%d= %ld\n",n,p);
   }	
while(1);
}
