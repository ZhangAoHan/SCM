#include "stdio.h"
#include "reg51.h"
  idata unsigned char C1 _at_ 0x22;
	idata unsigned char B1 _at_ 0x24;
  idata unsigned char D1 _at_ 0x26;
	idata unsigned int e  _at_ 0x28;
void main()
{
	C1=100;
	B1=90;
	SCON= 0x52;
  TMOD = 0x20;
  TCON = 0x69;
  TH1 = 0xF3;
	#pragma asm
	 MOV A,0x22
	 MOV B,0x24
   ADD A,B
   MOV 0x26,A
 #pragma endasm
	e=D1;
	printf("%d\n",e);
	while(1);
 	
}