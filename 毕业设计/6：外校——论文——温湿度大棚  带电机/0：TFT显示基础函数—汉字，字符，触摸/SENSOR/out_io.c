#include "out_io.h"

void IO_Init(void)
{
	RCC->APB2ENR|=1<<7;    //Ê¹ÄÜPORTfÊ±ÖÓ	   	 
	   	 
	GPIOF->CRL&=0XFFFF00FF; 
	GPIOF->CRL|=0X00003300;   	 
    GPIOF->ODR|=3<<2;      
											
}

