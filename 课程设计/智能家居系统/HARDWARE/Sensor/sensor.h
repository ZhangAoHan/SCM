#ifndef __SENSOR_H
#define __SENSOR_H	
#include "sys.h"
#define ADC_CH1  1  	//ͨ��1		 	    
	   									   
void Adc_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 
#endif 
