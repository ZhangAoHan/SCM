#include "stdio.h"
#include "reg51.h"
 void main()
{
	int a;
	SCON= 0x52;                     
  TMOD = 0x20;   
  TCON = 0x69;    
  TH1 = 0xF3; 
  scanf("%d",&a);
	switch(a)
	{
		case 1:    puts("January\n");                        break;
	  case 2:    puts("February\n");                       break;
    case 3:    puts("March\n");                          break;
	  case 4:    puts("April\n");                          break;
	  case 5:    puts("May\n");                            break;
	  case 6:    puts("June\n");                           break;
	  case 7:    puts("July\n");                           break;
	  case 8:    puts("August\n");                         break;
	  case 9:    puts("September\n");                      break;
	  case 10:   puts("October\n");                        break;
	  case 11:   puts("November\n");                       break;
	  case 12:   puts("December\n");                       break;
	  default :  puts("input number should be in 1~12\n"); 
	}
}