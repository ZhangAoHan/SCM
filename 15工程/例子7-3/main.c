#include "reg51.h"
sfr  WDT_CONTR=0xc1;

void main()
{
	long unsigned int j;
	char c=0x10;
	  P46=0;
	  P47=0;
	  for(j=0;j<99999;j++);
	  P46=1;
	  P47=1;
	  while(1)
			WDT_CONTR|=c;
}