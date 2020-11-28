/*   spi.h   */

#ifndef __SPI_H
#define __SPI_H


#include "sys.h"



#define SPI1_CS_H() GPIOA->BSRR=GPIO_Pin_4
#define SPI1_CS_L() GPIOA->BRR =GPIO_Pin_4


#define SPI2_CS_H() GPIOB->BSRR=GPIO_Pin_12
#define SPI2_CS_L() GPIOB->BRR =GPIO_Pin_12







void SPI1_Init(void);			       //��ʼ��SPI1��
void SPI1_SetSpeed(u8 SpeedSet);   //����SPI1�ٶ�  		 
u8 SPI1_ReadWriteByte(u8 TxData);  //SPI1���߶�дһ���ֽ�

void SPI2_Init(void);			        //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet);    //����SPI�ٶ�
u8 SPI2_ReadWriteByte(u8 TxData);   //SPI���߶�дһ���ֽ�
		 
#endif

