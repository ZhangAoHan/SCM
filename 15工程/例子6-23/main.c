#include "stdio.h"
#include "reg51.h"
 main()
{
    int i,j,l;
	  float k;
	  char c1;
	  SCON= 0x52;                     
    TMOD = 0x20;   
    TCON = 0x69;    
    TH1 = 0xF3;   
	  scanf("%d,%d,%c",&i,&j,&c1);
	  scanf("%f",&k);
	  getchar();
	  scanf("%c",&c1);
	  printf("\ni=%d,j=%d\n",i,j);
	  printf("k=%f\n",k);
	  printf("c=%c\n",c1);
	return 1;
}
	
