#ifndef __IIC_H
#define __IIC_H
#include "sys.h"

//IO��������
#define sDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define sDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO��������	 
#define iIC_SCL    PCout(12) //SCL
#define iIC_SDA    PCout(11) //SDA	 
#define rEAD_SDA   PCin(11)  //����SDA 

//IIC���в�������
void iIC_Init(void);                //��ʼ��IIC��IO��				 
void iIC_Start(void);				//����IIC��ʼ�ź�
void iIC_Stop(void);	  			//����IICֹͣ�ź�
void iIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 iIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 iIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void iIC_Ack(void);					//IIC����ACK�ź�
void iIC_NAck(void);				//IIC������ACK�ź�

void iIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 iIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif


