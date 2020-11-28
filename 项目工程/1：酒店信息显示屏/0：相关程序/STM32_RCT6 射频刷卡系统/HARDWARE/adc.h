#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

#define ADC_CH0  0  //通道0
#define ADC_CH1  1  //通道1
#define ADC_CH2  2  //通道2
#define ADC_CH3  3  //通道3
#define TEMP_CH  16 //温度传感器通道
	   
u16 Get_Temp(void);  //取得温度值
void Adc_Init(void); //ADC通道初始化
u16  Get_Adc(u8 ch); //获得某个通道值  	  
#endif 















