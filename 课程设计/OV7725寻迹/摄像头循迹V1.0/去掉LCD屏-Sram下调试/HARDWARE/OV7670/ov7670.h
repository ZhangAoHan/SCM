#ifndef _OV7670_H
#define _OV7670_H


#include "sys.h"
#include "sccb.h"



#define OV7670_VSYNC  	PAin(15)		//ͬ���źż��IO
#define OV7670_WRST		PAout(0)		//дָ�븴λ
#define OV7670_WREN		PAout(12)		//д��FIFOʹ��
#define OV7670_RCK		PAout(1)		//������ʱ��
#define OV7670_RRST		PAout(4)  		//��ָ�븴λ
#define OV7670_CS		PAout(11)  		//Ƭѡ�ź�(OE)



																		  					 
#define OV7670_DATA   GPIO_ReadInputData(GPIOB,0x00FF) 					//��������˿�
//#define OV7670_DATA   GPIOB->IDR&0x00FF   
/////////////////////////////////////////


#define CHANGE_REG_NUM 							171			//��Ҫ���õļĴ�������
extern const u8 ov7670_init_reg_tbl[CHANGE_REG_NUM][2];		//�Ĵ����������ñ�


u8 camera_refresh(void);	    				 
u8   OV7670_Init(void);		  	   		 
void OV7670_Light_Mode(u8 mode);
void OV7670_Color_Saturation(u8 sat);
void OV7670_Brightness(u8 bright);
void OV7670_Contrast(u8 contrast);
void OV7670_Special_Effects(u8 eft);
void OV7670_Window_Set(u16 sx,u16 sy,u16 width,u16 height);


#endif





















