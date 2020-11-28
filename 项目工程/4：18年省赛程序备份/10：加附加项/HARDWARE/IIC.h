#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
   		   
//IO方向设置
#define SDA_IN()  {GPIOC->CRL&=0XFFFFFFF0;GPIOC->CRL|=8<<0;}
#define SDA_OUT() {GPIOC->CRL&=0XFFFFFFF0;GPIOC->CRL|=3<<0;}

//IO操作函数	 
#define IIC_SCL    PCout(1) //SCL
#define IIC_SDA    PCout(0) //SDA	 
#define READ_SDA   PCin(0)  //输入SDA 

//IIC所有操作函数
void IIC_Init1(void);                //初始化IIC的IO口				 
void IIC_Start1(void);				//发送IIC开始信号
void IIC_Stop1(void);	  			//发送IIC停止信号
void IIC_Send_Byte1(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte1(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack1(void); 				//IIC等待ACK信号
void IIC_Ack1(void);					//IIC发送ACK信号
void IIC_NAck1(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte1(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte1(u8 daddr,u8 addr);	  
#endif
















