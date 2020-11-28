#ifndef __SENSOR_H
#define __SENSOR_H	
#include "sys.h"
#define ADC_CH1  1  	//通道1		 	    
	   									   
void Adc_Init(void); 				//ADC通道初始化
u16  Get_Adc(u8 ch); 				//获得某个通道值 
u16 Get_Adc_Average(u8 ch,u8 times);//得到某个通道10次采样的平均值 
#endif 
