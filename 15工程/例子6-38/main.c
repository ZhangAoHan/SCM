#include "stdio.h"
#include "reg51.h"
void main()
{
	char data a=100;
	char data *p1;
	char data **p2;
	SCON= 0x52;                           
  TMOD = 0x20;                   
  TCON = 0x69;           
  TH1 = 0xF3;
	p1=&a;
	p2=&p1;
	printf("%c\n",**p2);
	while(1);
}