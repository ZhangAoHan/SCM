#include "stdio.h"
#include "reg51.h"
enum color{red,green,blue};
enum color i,j,k,st;
void main()
{
	int n=0,m;
	SCON= 0x52;
  TMOD = 0x20;
  TCON = 0x69;
  TH1 = 0xF3;
 
	 for(i=red;i<=blue;i++)
	    for(j=red;j<=blue;j++)
				for(k=red;k<=blue;k++)
			  {
               n=n+1;
					printf("%-4d",n);					
					  for(m=1;m<=3;m++)
					    {
								 switch(m)
								 {
									 case 1 : st=i;break;
									 case 2:  st=j;break;
									 case 3:  st=k;break;
									 default: break;
								 }
								 switch(st)
								 {
									 case red  :  printf("%-10s","red");break;
									 case green:  printf("%-10s","green");break;
									 case blue :  printf("%-10s","blue");break;
									 default: break;
								 }
							 }
				 printf("\n");
				}
				printf("\n total:%5d\n",n);
	 while(1);
}