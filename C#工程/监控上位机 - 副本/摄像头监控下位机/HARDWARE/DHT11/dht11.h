#ifndef __DHT11_H
#define __DHT11_H	
#include "sys.h"
#define ADC_CH1  1  	//ͨ��1		 	    
//IO��������
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=0X00000800;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=0X00000300;}
//IO��������                                                                              
#define    DHT11_DQ_OUT PAout(2) //���ݶ˿�    
#define    DHT11_DQ_IN  PAin(2)  //���ݶ˿�      									   
void Adc_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 

void DHT11_Init(void);           //��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void); //����һ���ֽ�
u8 DHT11_Read_Bit(void);   //����һ��λ
u8 DHT11_Check(void);       //����Ƿ����DHT11
void DHT11_Rst(void);         //��λDHT11   
#endif 





