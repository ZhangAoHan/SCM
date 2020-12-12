#include "stdio.h"
#include "reg51.h"
void main()
{
	  char a,b,c;
    SCON= 0x52;                     
    TMOD = 0x20;   
    TCON = 0x69;    
    TH1 = 0xF3;
    a=getchar();
    b=getchar();
    c=getchar();
    putchar('\n');
    putchar(a);
    putchar(b);
    putchar(c);
   	putchar('\n');
}