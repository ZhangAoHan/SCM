#include "stdio.h"
#include "reg51.h"

void sort(int array[],int n)
{
	int i,j,k,t;
	for(i=0;i<n-1;i++)
	  {
			k=i;
			  for(j=k+1;j<n;j++)
			     if(array[j]<array[k])
						 k=j;
					 t=array[k];
					 array[k]=array[i];
					 array[i]=t;
		}
}

void main()
{
	int a[10],i;
	SCON= 0x52;
  TMOD = 0x20;
  TCON = 0x69;
  TH1 = 0xF3;
	printf("please enter the value of a[10]\n");
	for(i=0;i<10;i++)
	  scanf("%d,",&a[i]);
	printf("\n sorted array is\n");
	sort(a,10);
	for(i=0;i<10;i++)
	  printf("a[%d]=%d,",i,a[i]);
	while(1);
	
}