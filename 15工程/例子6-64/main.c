#include "reg51.h"
int i=0;

servivce_int0() interrupt 0
{
	if(i==4) i=0;
	if(i==0)
	{
		P46=1;
		P47=1;
  }		
	else if(i==1)
	{
		P46=0;
		P47=1;
  }		
	else if(i==2)
	{
		P46=1;
		P47=0;
  }	
	else if(i==3)
	{
		P46=0;
		P47=0;
  }		
	i=i+1;
}

void main()
{
	//INT0=1;
	IT0=1;
	EX0=1;
	EA=1;
  while(1);
}