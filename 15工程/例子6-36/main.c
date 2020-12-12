#include "stdio.h"
#include "reg51.h"
void main()
{
	int a=100;
	int b[4]={1,2,3,4};
	char c[10]={"STC"};
	int *p1,*p2;
	char *p3;
	SCON= 0x52;                           
  TMOD = 0x20;                   
  TCON = 0x69;           
  TH1 = 0xF3;    
	p1=&a;
	p2=&b;
	p3=&c;
	printf("%d\n",*p1);
	printf("%d,",*p2);
	printf("%d,",*(++p2));
	printf("%d,",*(++p2));
	printf("%d,\n",*(++p2));
	printf("%c",*p3);
	printf("%c",*(++p3));
	printf("%c\n",*(++p3));
	while(1);
}