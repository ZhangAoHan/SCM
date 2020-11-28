#define TLC2543_GLOBAL
#include "TLC2543.h"

uint read_TLC2543(uchar channel)
{
    register uchar i;
    uint tempAD = 0;

    while(!TLC2543GetEoc());        //wait TLC2543 free
	_delay_us(3);
    channel <<= 4;

    TLC2543Clk(TLC2543_CLR);
    TLC2543_Cs(TLC2543_SET);
    TLC2543_Cs(TLC2543_CLR);                //_CS TLC2543 select

	_delay_us(3);
    for( i = 0; i < 12; i ++ )
    {
        tempAD <<= 1;
        if( TLC2543GetDo() )        //read value
        {
            tempAD |= 0x01;
        }
        if( channel&0x80 )
        {
            TLC2543Di(TLC2543_SET);
        }
        else
        {
            TLC2543Di(TLC2543_CLR);
        }
        channel <<= 1;
        TLC2543Clk(TLC2543_SET);
        nop();
        TLC2543Clk(TLC2543_CLR);
    }

    TLC2543_Cs(TLC2543_SET);                //TLC2543 close
	_delay_us(1);

    return tempAD;
}
 void _delay_us(uint us)
{
   uchar delayi;
   while(--us)
   {
	 for(delayi=0;delayi<10;delayi++);
   } 
}															  
