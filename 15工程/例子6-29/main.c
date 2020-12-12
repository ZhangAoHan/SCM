#include "stdio.h"
#include "reg51.h"
void main()
{
	 int a;
	  SCON= 0x52;                     
    TMOD = 0x20;   
    TCON = 0x69;    
    TH1 = 0xF3; 
	
	loop:
	      puts("please input 0 to end loop\n");
	      scanf("%d",&a);
	      if(a!=0) 
	          goto loop;
				else
		        puts("end program\n");
}