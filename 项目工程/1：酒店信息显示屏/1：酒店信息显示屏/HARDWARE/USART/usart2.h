#ifndef __USART2_H
#define __USART2_H
#include "sys.h"
#include "stdio.h"	 
#define USART_REC_LEN2  			200  
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF2[USART_REC_LEN2]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA2;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void usart2_init(u32 pclk2,u32 bound);
#endif	   
