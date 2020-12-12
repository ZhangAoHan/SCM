#include "stdio.h"
#include "reg51.h"
void main()
{
	int a[4]={0x01,0x10,0x100,0x1000};
	int *b[4]={&a[0],&a[1],&a[2],&a[3]};
	int **p2;
	int i;
  SCON= 0x52;
  TMOD = 0x20; 
  TCON = 0x69; 
  TH1 = 0xF3;
	p2=b;
  for(i=0;i<4;i++)	
  printf("a[%d]=%d,",i,a[i]);
	putchar('\n');
	for(i=0;i<4;i++)	
  printf("a[%d]=%d,",i,**(p2++));
	putchar('\n');
	while(1);
}