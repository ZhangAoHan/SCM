#ifndef __DATE_H
#define __DATE_H	
#include "sys.h"

#define JDQ PAout(0)						  	 	    
#define ADC_CH1  1  	//ͨ��1		 
#define DHT11_IO_IN()  {GPIOC->CRH&=0X0FFFFFFF;GPIOC->CRH|=8<<28;}
#define DHT11_IO_OUT() {GPIOC->CRH&=0X0FFFFFFF;GPIOC->CRH|=3<<28;}
	////IO��������											   
#define	DHT11_DQ_OUT PCout(15) //���ݶ˿�	PG11 
#define	DHT11_DQ_IN  PCin(15)  //���ݶ˿�	PG11   									   
void Adc_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 
u8 DHT11_Init(void);		//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);	//����һ���ֽ�
u8 DHT11_Read_Bit(void);	//����һ��λ
u8 DHT11_Check(void);		//����Ƿ����DHT11
void DHT11_Rst(void);		//��λDHT11 
void Io_In_Out(void);
#endif 

