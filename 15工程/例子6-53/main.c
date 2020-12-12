#include "stdio.h"
#include "reg51.h"

void main()
{
	SCON= 0x52;
  TMOD = 0x20;
  TCON = 0x69;
  TH1 = 0xF3;

	#ifdef SYMBOL
   	printf("define SYMBOL in file\n");
	#else
	  printf("not define SYMBOL in file\n");
	#endif
	while(1);
}