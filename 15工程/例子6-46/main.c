#include "stdio.h"
#include "reg51.h"

int fac(int n) reentrant
{
	long int f;
	if(n<0) 
		 printf("data must be larger than 0\n");
	else if(n<1)
		f=1;
	else
		f=fac(n-1)*n;
	return f;
}

main()
{
	int n;
	long int y;
	SCON= 0x52;
  TMOD = 0x20;
  TCON = 0x69;
  TH1 = 0xF3;
	printf("please input an integer number\n");
	scanf("%d",&n);
	y=fac(n);
	printf("%d!=%ld\n",n,y);
  while(1);	
}