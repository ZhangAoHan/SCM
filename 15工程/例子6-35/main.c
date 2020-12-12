#include "stdio.h"
#include "reg51.h"
#define  row_a 4
#define  col_a 3
#define  row_b 3
#define  col_b 2
void main()
{
	 int a[row_a][col_a];
	 int b[row_b][col_b];
   int c[row_a][col_b];	
	 int i,j,k;
	 int m,n,o,p; 
	 SCON= 0x52;                     
   TMOD = 0x20;   
   TCON = 0x69;    
   TH1 = 0xF3;                  
	 m=row_a;
	 n=col_a;
	 o=row_b;
	 p=col_b;
	 printf("please input data of a[%d][%d]\n",m,n);
	 for(i=0;i<row_a;i++)                  
	{
	     for(j=0;j<col_a;j++)               
	       scanf("%d,",&a[i][j]);        
	}
	putchar('\n');   
	
	 printf("please input data of b[%d][%d]\n",o,p);
	 for(i=0;i<row_b;i++)                  
	{
	     for(j=0;j<col_b;j++)               
	       scanf("%d,",&b[i][j]);        
	}
	putchar('\n');    	
  for (i=0;i<row_a;i++)
  {
     for (j=0;j<col_b;j++)
      {
       c[i][j]=0;     
         for (k=0;k<col_a;k++)
        {
           c[i][j]+=a[i][k]*b[k][j];
        }
      }
  }                   
	printf("\n array c[%d][%d] is following\n",m,p);
	 for(i=0;i<row_a;i++)
	{
	     for(j=0;j<col_b;j++)
	       printf("%5d,",c[i][j]); 
		     putchar('\n');                
	}                  
while(1);
}
