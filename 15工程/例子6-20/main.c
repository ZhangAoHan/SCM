#include "stdio.h"
#include "reg51.h"
void main()
{
	char a='S',b='T',c='C';
	char d='\n';
	char e='H',f='e',g='l',h='l',i='o';
	SCON= 0x52;                     
  TMOD = 0x20;   
  TCON = 0x69;    
  TH1 = 0xF3;                        
	putchar(a);
	putchar(b);
	putchar(c);
	putchar(d);
	putchar(e);
	putchar(f);
	putchar(g);
	putchar(h);
	putchar(i);
	putchar(d);
}