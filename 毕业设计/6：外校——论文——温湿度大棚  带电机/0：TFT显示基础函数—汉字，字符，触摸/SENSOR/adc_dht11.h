#ifndef __ADC_DHT11_H
#define __ADC_DHT11_H
#include "delay.h"	
#include "sys.h"
//IO��������
#define DHT11_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
#define DHT11_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
////IO��������											   
#define	DHT11_DQ_OUT PGout(11) //���ݶ˿�	PG11 
#define	DHT11_DQ_IN  PGin(11)  //���ݶ˿�	PG11

#define ADC_CH1  1  				//ͨ��1(������PA1)	 	    

void  Adc_Init(void);
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);

u8 DHT11_Init(void);		//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);	//����һ���ֽ�
u8 DHT11_Read_Bit(void);	//����һ��λ
u8 DHT11_Check(void);		//����Ƿ����DHT11
void DHT11_Rst(void);		//��λDHT11    


#endif

