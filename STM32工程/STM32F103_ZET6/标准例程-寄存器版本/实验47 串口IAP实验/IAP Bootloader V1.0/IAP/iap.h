#ifndef __IAP_H__
#define __IAP_H__
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//IAP ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/27
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////	    
typedef  void (*iapfun)(void);				//����һ���������͵Ĳ���.   
#define FLASH_APP1_ADDR		0x08009000  	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
											//����0X08000000~0X08008FFF�Ŀռ�ΪBootloaderʹ��	   
void iap_load_app(u32 appxaddr);			//��ת��APP����ִ��
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 applen);	//��ָ����ַ��ʼ,д��bin
#endif







































