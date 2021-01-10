#ifndef __TSC2046_H__
#define __TSC2046_H__

#define PENDIRQ GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define uint8  unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int

#define FACX	7.95	 //����ϵ��,��ֵ�;������Ļ�й�ϵ
#define FACY	14.10	 //������ֵ��ʵ��ó��Ľ��.

//  #define ADJMODE		 //������У׼����ϵ��ģʽ
#define CONSTMODE		 //����ϵ������ʵ��ֵģʽ

void SPI_Config(void);
void TSC2046_Config(void);
uint16 TP_ReadX(void);
uint16 TP_ReadY(void);
void TP_Read(uint16 *tpx,uint16 *tpy);
void BubbleSort(uint16 a[],uint8 n);
uint8 SPI_WriteByte(uint8 dat);
uint8 SPI_ReadByte(void);
void TP_ADtoZB(uint16 *tpx,uint16 *tpy,uint16 *x,uint16 *y);
void TouchScreenAdjust(void);

#endif
