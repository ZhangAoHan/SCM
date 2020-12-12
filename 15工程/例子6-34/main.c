#include "stdio.h"
#include "reg51.h"
void main()
{
	 int a[8];
	 int b[3][3];
	 xdata char str[40];
	 int i,j;
	 SCON= 0x52;                     
   TMOD = 0x20;   
   TCON = 0x69;    
   TH1 = 0xF3;
	 printf("please input data of a[8]\n");
	 for(i=0;i<8;i++)
	   scanf("%d,",&a[i]);
	   putchar('\n');
	
	 printf("please input data of b[3][3]\n");
	 for(i=0;i<3;i++)
	{
	     for(j=0;j<3;j++)
	       scanf("%d,",&b[i][j]);
	}
	putchar('\n');
	
	printf("please input string of str[40]\n");
	  // scanf("%s,",str);
	  // gets(str,40);
for(i=0;i<40;i++)
   {
		scanf("%c",&str[i]);
	  if(str[i]=='\n') break;
	 }
	putchar('\n');
	for(i=0;i<8;i++)
	   printf("a[%d]=%d,",i,a[i]);
	 printf("\n");
	 for(i=0;i<3;i++)
	{
	     for(j=0;j<3;j++)
	       printf("b[%d][%d]=%d,",i,j,b[i][j]);
		     putchar('\n');
	}
	     puts(str);
while(1);
}