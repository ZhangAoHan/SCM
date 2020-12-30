#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
  
//IO��������
#define DHT11_IO_IN()  {GPIOC->CRL&=0X0FFFFFFF;GPIOC->CRL|=(unsigned int)8<<28;}
#define DHT11_IO_OUT() {GPIOC->CRL&=0X0FFFFFFF;GPIOC->CRL|=(unsigned int)3<<28;}
////IO��������											   
#define	DHT11_DQ_OUT PCout(7) //���ݶ˿�	PG11 
#define	DHT11_DQ_IN  PCin(7)  //���ݶ˿�	PG11


u8 DHT11_Init(void);		//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);	//����һ���ֽ�
u8 DHT11_Read_Bit(void);	//����һ��λ
u8 DHT11_Check(void);		//����Ƿ����DHT11
void DHT11_Rst(void);		//��λDHT11    
#endif















