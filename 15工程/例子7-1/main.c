#include "reg51.h"
sfr CLK_DIV =0x97;
void main()
{
	CLK_DIV=0xc5;
	while(1);
}