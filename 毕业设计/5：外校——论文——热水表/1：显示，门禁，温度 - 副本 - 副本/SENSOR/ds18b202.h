#ifndef __DS18B202_H
#define __DS18B202_H 
#include "sys.h"   

//IO��������
#define DS18B202_IO_IN()  {GPIOB->CRH&=0XFFFFF0FF;GPIOB->CRH|=8<<8;}
#define DS18B202_IO_OUT() {GPIOB->CRH&=0XFFFFF0FF;GPIOB->CRH|=3<<8;}
////IO��������											   
#define	DS18B202_DQ_OUT PBout(10) //���ݶ˿�	PA0
#define	DS18B202_DQ_IN  PBin(10)  //���ݶ˿�	PA0 
   	
u8 DS18B202_Init(void);			//��ʼ��DS18B20
short DS18B202_Get_Temp(void);	//��ȡ�¶�
void DS18B202_Start(void);		//��ʼ�¶�ת��
void DS18B202_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B202_Read_Byte(void);		//����һ���ֽ�
u8 DS18B202_Read_Bit(void);		//����һ��λ
u8 DS18B202_Check(void);			//����Ƿ����DS18B20
void DS18B202_Rst(void);			//��λDS18B20    
#endif















