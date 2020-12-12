#include "stdio.h"
#include "reg51.h"

void con_string(char *s1, char *s2 )       
{
	while(*s1!='\0') 
		 s1++;
  while(*s2!='\0')
		 *s1++=*s2++;
	   *s1='\0';
}
  

void main()
{
	xdata char  a[40],b[40];
	SCON= 0x52;
    TMOD = 0x20;
    TCON = 0x69;
    TH1 = 0xF3;
	printf("please enter the string of a[40]\n");
	  gets(a,40);
	printf("please enter the string of b[40]\n");
    gets(b,40);	
	printf("\n connected the string is\n");
	con_string(a,b);    
   puts(a);	
	while(1);
	
}
