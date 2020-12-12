#include "stdio.h"
#include "reg51.h"
union {
       char data_str[8];
       struct {
				        int  a;
                int  b;
                long int c; 				 
				
          }data_var;
				}shared_information;
void main()
{
	int i;
	SCON= 0x52;
  TMOD = 0x20;
  TCON = 0x69;
  TH1 = 0xF3;
  shared_information.data_var.a=100;
	shared_information.data_var.b=1000;
	shared_information.data_var.c=100000000;
	 for(i=0;i<8;i++)
    { 
		 printf("data[%d]=%c,\n",i,shared_information.data_str[i]);
	 } 
	 while(1);
}