#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

#define ADC_CH0  0  //ͨ��0
#define ADC_CH1  1  //ͨ��1
#define ADC_CH2  2  //ͨ��2
#define ADC_CH3  3  //ͨ��3
#define TEMP_CH  16 //�¶ȴ�����ͨ��
	   
u16 Get_Temp(void);  //ȡ���¶�ֵ
void Adc_Init(void); //ADCͨ����ʼ��
u16  Get_Adc(u8 ch); //���ĳ��ͨ��ֵ  	  
#endif 















