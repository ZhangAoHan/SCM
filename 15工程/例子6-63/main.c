#include "reg51.h"
void main()
{
int i=0;
long  int j=0;
	while(1)
	{
	 for(i=0;i<4;i++)
		{
			switch(i)
			{
				case 0:
				{
	          P46=1;
	          P47=1;
				}
				   break;
			  case 1:
				{
	          P46=0;
	          P47=1;
				}
				   break;
				case 2:
				{
	          P46=1;
	          P47=0;
				}
				   break;
				case 3:
				{
	          P46=0;
	          P47=0;
				}
				   break;
				default :  ;
			}
		 for(j=0;j<222222;j++){;}
		 }
    }
	}