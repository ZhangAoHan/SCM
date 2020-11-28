#ifndef __OLCD_H
#define __OLCD_H
#include "sys.h"

//IO方向设置
#define sDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define sDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO操作函数	 
#define iIC_SCL    PCout(12) //SCL
#define iIC_SDA    PCout(11) //SDA	 
#define rEAD_SDA   PCin(11)  //输入SDA 

//IIC所有操作函数
void iIC_Init(void);                //初始化IIC的IO口				 
void iIC_Start(void);				//发送IIC开始信号
void iIC_Stop(void);	  			//发送IIC停止信号
void iIC_Write_Byte(u8 date);			//IIC发送一个字节
u8 iIC_Read_Byte(unsigned char cmd);//IIC读取一个字节
u8 iIC_Wait_Ack(void); 				//IIC等待ACK信号
void iIC_Ack(void);					//IIC发送ACK信号
void iIC_NAck(void);				//IIC不发送ACK信号

void iIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 iIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
