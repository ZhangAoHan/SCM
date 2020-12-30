#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART1_RX_BUF[64],USART2_RX_BUF[64],USART3_RX_BUF[64]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART1_RX_STA,USART2_RX_STA,USART3_RX_STA;         		//����״̬���	
 
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 pclk2,u32 bound);
#define EN_USART2_RX    1//ʹ�ܴ���2����
#define EN_USART3_RX    1//ʹ�ܴ���2����
void uart2_init(u32 pclk2,u32 bound);
void uart3_init(u32 pclk2,u32 bound);
#endif	   
















