#include "stdio.h"
#include "reg51.h"

#define PI 3.14115926
#define CIRCLE(R,L,S) L=2*PI*R; S=PI*(R)*(R)
#define MAX(x,y)   (((x)>(y)) ? (x) : (y))
void main()
{
	  float r,l,s;
	  int a,b;
    SCON= 0x52;
    TMOD = 0x20;
    TCON = 0x69;
    TH1 = 0xF3;
	  printf("please input r:\n");
	  scanf("%f",&r);
	  printf("please input value of a and b\n");
	  scanf("%d,%d",&a,&b);
	  CIRCLE(r,l,s);
	  printf("\nr=%f\ncirc=%f\narea=%f\n",r,l,s);
	  printf("a=%d, b=%d, max value is %d\n",a,b,MAX(a,b));
	  while(1);
}