#include "stdio.h"
#include "reg51.h"
void main()
{
	int a=10,*p1;
	int i;
	char b[40],*s;
	xdata char c[50],*s1="STC hello";
	xdata int d[4]={1,2,3,4},*p2;
	SCON= 0x52;
  TMOD = 0x20; 
  TCON = 0x69; 
  TH1 = 0xF3;
	p1=&a;
	s=&b;
	s1=&c;
	p2=&d;
	printf("please input int value of pointer p1\n");
  scanf("%d",p1);
	printf("please input string value of pointer s\n");
	scanf("%s",s);
	printf("please input string value of pointer s1\n");
	scanf("%s",s1);
	printf("please input int value of pointer p2\n");
	for(i=0;i<4;i++)
   {	   
	    scanf("%d",p2);
	         p2++;
}
	printf("the address of p1= %p\n",p1);
	printf("the value of p1(p1)=%d\n",*p1);
	printf("the value of a=%d\n",a);
	printf("the address of s=%p\n",s);
	printf("the value of s1=\"%s\"\n",s);
  printf("the value of b[40]=\"%s\"\n",b);
  printf("the address of s1=%p\n",s1);
	printf("the value of s1=\"%s\"\n",s1);
  printf("the value of c[50]=\"%s\"\n",c);
  p2=&d;
  for(i=0;i<4;i++)
   {	   
	    printf("P2[%d]=%d,",i,*p2);
		  p2++;
}
	  putchar('\n');
for(i=0;i<4;i++)
   {	   
	    printf("d[%d]=%d,",i,d[i]);
}
	while(1);
}