#include "stdio.h"
#include "reg51.h"

void main()
{
	int a=10;
	float b=133452.1243;
	char s1[20]={"STC Hello"};
	char c1='a';
	  SCON= 0x52;                     
    TMOD = 0x20;   
    TCON = 0x69;    
    TH1 = 0xF3;
	printf("%d\n",a);
	printf("%f\n",b);
	printf("%7.2f\n",b);
	printf("%e\n",b);
	printf("%s\n",s1);
	printf("%c\n",c1);
	printf("%d,%f\n",a,b);
  printf("a=%d, b=%d\n",a,b);
}