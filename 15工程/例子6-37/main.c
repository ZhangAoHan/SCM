#include "stdio.h"
#include "reg51.h"
void main()
{
	int a=100,b=10,t=0;
	int *p1,*p2,*p3;
  SCON= 0x52;
  TMOD = 0x20; 
  TCON = 0x69; 
  TH1 = 0xF3; 
  printf("a=%d,b=%d\n",a,b);
	p1=&a;
	p2=&b;
	p3=p1;
	p1=p2;
	p2=p3;
	printf("*p1=%d,*p2=%d\n",*p1,*p2);
	printf("a=%d,b=%d\n",a,b);
	p1=&a;
	p2=&b;
	t=*p1;
	*p1=*p2;
	*p2=t;
	printf("*p1=%d,*p2=%d\n",*p1,*p2);
	printf("a=%d,b=%d\n",a,b);
	while(1);
}