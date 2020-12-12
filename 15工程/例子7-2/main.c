#include "reg51.h"
sfr  IAP_CONTR=0xc7;

void main()
{
	long unsigned int j;
	  P41=0;
	  P42=0;
	  for(j=0;j<999999;j++);
	  P41=1;
	  P42=1;
	  for(j=0;j<999999;j++);
	  P41=0;
	  P42=0;
	  for(j=0;j<999999;j++);
	  IAP_CONTR=0x60;
}