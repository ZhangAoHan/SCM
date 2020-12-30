#include "date.h"

u8 temperature;  	    
u8 humidity;  	
u16 adcx;	

void date_read(void)
{
	DHT11_Read_Data(&temperature,&humidity);
	adcx=Get_Adc_Average(ADC_CH1,5);
}





