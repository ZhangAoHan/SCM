#include <rtx51tny.h>
unsigned char counter0;
unsigned char counter1;
void job0(void) _task_ 0 
{
   os_create_task(1); 
   while (1) 
		{
      if (++counter0 == 0) 
      os_send_signal (1); 
    }
}

void job1(void) _task_ 1 
{
   while (1)
	  { 
      os_wait(K_SIG,0,0); 
      counter1++;
    }
}

