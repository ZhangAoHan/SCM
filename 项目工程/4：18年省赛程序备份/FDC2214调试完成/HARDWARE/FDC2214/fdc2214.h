#ifndef __FDC2214_H
#define __FDC2214_H
#include "sys.h"

//IO��������
#define FDC_SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}		//PA11 SCL PA12  SDA 
#define FDC_SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//IO��������	 
#define FDC_IIC_SCL    PBout(10) 	//SCL
#define FDC_IIC_SDA    PBout(11)   //���SDA	 
#define FDC_READ_SDA   PBin(11) 		//����SDA 

/*FDC2214    iic�ӵ�ַ
 *ADDR = L , I2C Address = 0x2A
 *ADDR = H , I2C Address = 0x2B*/

#define FDC2214_ADDR 0x2A

/*FDC2214�����Ĵ�����ַ*/

#define DATA_CH0 0x00     				//���ݼĴ���
#define DATA_LSB_CH0 0x01
#define DATA_CH1 0x02
#define DATA_LSB_CH1 0x03
#define DATA_CH2 0x04
#define DATA_LSB_CH2 0x05
#define DATA_CH3 0x06
#define DATA_LSB_CH3 0x07

#define RCOUNT_CH0 0x08   			 //ת��ʱ��  tCx = (CHx_RCOUNT *16 + 4) /fREFx
#define RCOUNT_CH1 0x09
#define RCOUNT_CH2 0x0A
#define RCOUNT_CH3 0x0B

#define OFFSET_CH0 0x0C  				//Ƶ��ƫ�ƼĴ���
#define OFFSET_CH1 0x0D
#define OFFSET_CH2 0x0E
#define OFFSET_CH3 0x0F

#define SETTLECOUNT_CH0 0x10			//����ʱ�� tSx = (CHX_SETTLECOUNT*16)/fREFx
#define SETTLECOUNT_CH1 0x11
#define SETTLECOUNT_CH2 0x12
#define SETTLECOUNT_CH3 0x13

#define CLOCK_DIVIDERS_C_CH0 0x14       //ʱ�ӷ�Ƶ
#define CLOCK_DIVIDERS_C_CH1 0x15
#define CLOCK_DIVIDERS_C_CH2 0x16
#define CLOCK_DIVIDERS_C_CH3 0x17

#define STATUS 0x18                     //״̬�Ĵ���
#define ERROR_CONFIG 0x19 				//���󱨸�����

#define CONFIG 0x1A  
#define MUX_CONFIG 0x1B
#define RESET_DEV 0x1C
#define DRIVE_CURRENT_CH0 0x1E          //��������
#define DRIVE_CURRENT_CH1 0x1F
#define DRIVE_CURRENT_CH2 0x20
#define DRIVE_CURRENT_CH3 0x21
#define MANUFACTURER_ID 0x7E      //��ȡֵ��0x5449
#define DEVICE_ID 0x7F            //��ȡֵ��0x3055

//extern u16 Data_FDC;

//��غ�������
u8 Set_FDC2214(u8 reg,u8 MSB,u8 LSB);

u16 FDC_Read(u8 reg);

//u16 FCD2214_ReadCH(u8 index);
u32 FCD2214_ReadCH(u8 index);
u8 FDC2214_Init(void);

float Cap_Calculate(u8 index);

#endif
