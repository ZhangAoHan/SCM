#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
   		   
//IO��������
#define SDA_IN()  {GPIOC->CRL&=0XFFFFFFF0;GPIOC->CRL|=8<<0;}
#define SDA_OUT() {GPIOC->CRL&=0XFFFFFFF0;GPIOC->CRL|=3<<0;}

//IO��������	 
#define IIC_SCL    PCout(1) //SCL
#define IIC_SDA    PCout(0) //SDA	 
#define READ_SDA   PCin(0)  //����SDA 

//IIC���в�������
void IIC_Init1(void);                //��ʼ��IIC��IO��				 
void IIC_Start1(void);				//����IIC��ʼ�ź�
void IIC_Stop1(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte1(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte1(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack1(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack1(void);					//IIC����ACK�ź�
void IIC_NAck1(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte1(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte1(u8 daddr,u8 addr);	  
#endif
















