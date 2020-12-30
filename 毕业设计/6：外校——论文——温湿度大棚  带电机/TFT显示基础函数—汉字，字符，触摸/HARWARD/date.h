#ifndef __DATE_H
#define __DATE_H	
#include "sys.h"
			

//IO��������
#define DHT11_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
#define DHT11_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
#define DHT12_IO_IN()  {GPIOG->CRH&=0XFFFFF0FF;GPIOG->CRH|=8<<8;}
#define DHT12_IO_OUT() {GPIOG->CRH&=0XFFFFF0FF;GPIOG->CRH|=3<<8;}
////IO��������											   
#define	DHT11_DQ_OUT PGout(11) //���ݶ˿�	PG11 
#define	DHT11_DQ_IN  PGin(11)  //���ݶ˿�	PG11
#define	DHT12_DQ_OUT PGout(10) //���ݶ˿�	PG11 
#define	DHT12_DQ_IN  PGin(10)  //���ݶ˿�	PG11

#define ADC_CH1  1  				//ͨ��1(������PA1)	 	
#define ADC_CH2  2  	
#define ADC_CH3  3 	           //����
#define ADC_CH4  4  	          //����
#define ADC_CH0  0 	
u8 DHT12_Init(void);		//��ʼ��DHT11
u8 DHT12_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT12_Read_Byte(void);	//����һ���ֽ�
u8 DHT12_Read_Bit(void);	//����һ��λ
u8 DHT12_Check(void);		//����Ƿ����DHT11
void DHT12_Rst(void);		//��λDHT11 

u8 DHT11_Init(void);		//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);	//����һ���ֽ�
u8 DHT11_Read_Bit(void);	//����һ��λ
u8 DHT11_Check(void);		//����Ƿ����DHT11
void DHT11_Rst(void);		//��λDHT11 

void  Adc_Init(void);
void  Adc2_Init(void);
void  Adc3_Init(void);
void  Adc4_Init(void);
void  Adc0_Init(void);
u16 Get_Adc(u8 ch)  ;

u16 Get_Adc_Average(u8 ch,u8 times);

void date_read(void);
#endif 
