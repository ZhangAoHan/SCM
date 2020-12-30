#ifndef __ADC_H
#define __ADC_H 
#include "sys.h"   
#define ADC_CH1  1  				//通道1(连接在PA1)	 	
#define ADC_CH2  2  	
  
void  Adc_Init(void);
void  Adc2_Init(void); 
u16 Get_Adc(u8 ch)  ;

u16 Get_Adc_Average(u8 ch,u8 times);
#endif


