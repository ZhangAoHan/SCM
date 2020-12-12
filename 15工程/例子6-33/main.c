#include  "stdio.h"
#include "reg51.h"
void  main()
{
	int a[10]={0,1,2,3,4,5,6,7,8,9};
  int b[3][3]={{1,2,3},{4,5,6},{7,8,9}};     
	char c[20]={"STC Hello"};
	int i=0,j=0,k=0;
	 SCON= 0x52;                     
   TMOD = 0x20;   
   TCON = 0x69;    
   TH1 = 0xF3;
	 for(i=0;i<10;i++)
	   printf("a[%d]=%d  ",i,a[i]);
	   printf("\n");
   for(i=0;i<3;i++)
	 {
	    for(j=0;j<3;j++)
	        printf("b[%d][%d]=%d ",i,j,b[i][j]);
	    printf("\n");
	 }
	 for(i=0;i<20;i++)
	   {
	     if(c[i]=='\0') break;
	        printf("c[%d]=%c  ",i,c[i]);
		 }
	        printf("\n");
   while(1);
}