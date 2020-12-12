#include <reg51.h>
#include <self_define.h>
void main()
{
	char l;
	bit a=1;
	P4=0xFF;
	DP=0x30;
	ACC=10;
	B=5;
	l=ACC+B;
	    
}