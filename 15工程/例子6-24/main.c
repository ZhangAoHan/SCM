#include "stdio.h"
#include "reg51.h"
void main()
{
	int a, b,c;
	    SCON= 0x52;                     
      TMOD = 0x20;   
      TCON = 0x69;    
      TH1 = 0xF3;  
	    scanf("%d,%d,%d",&a,&b,&c);
	  if(a+b>c && b+c>a && a+c>b)
        if((a*a+b*b)==c*c)			
			    printf("a=%d,b=%d,c=%d is a right angle triangle\n",a,b,c);
				else
					printf("a=%d,b=%d,c=%d is not a right angle triangle\n",a,b,c);
		else
			    printf("a=%d,b=%d,c=%d is not a triangle\n",a,b,c);
}