#include <rtx51tny.h>
#include "reg51.h"
unsigned char counter0;
unsigned char counter1;
void job0(void) _task_ 0 
{
   os_create_task(1);
   while(1) 
  {
   counter0++; 
  }
}

void job1(void) _task_ 1 
{
  while(1) 
  { 
     counter1++; 
  }
}
