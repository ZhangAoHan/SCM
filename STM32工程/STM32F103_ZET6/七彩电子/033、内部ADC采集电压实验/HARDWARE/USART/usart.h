#ifndef __USART_H_
#define __USART_H_


#include "stdio.h"
#include "sys.h"


/***********************************************************************/
//������������(֧��USART1 USART2 USART3 UART4 UART5)
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//��ֲע�⣬���������е�STM32F103оƬ��֧��5������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/	 


void USART1_Init(u32 bound);//����1��ʼ������
void USART2_Init(u32 bound);//����2��ʼ������
void USART3_Init(u32 bound);//����3��ʼ������
void UART4_Init (u32 bound);//����4��ʼ������
void UART5_Init (u32 bound);//����5��ʼ������
//���ڷ���һ���ֽ�
void USART_SendByte(USART_TypeDef *USART_COM,u8 c);
//���ڷ������麯��
void USART_SendBuf(USART_TypeDef *USART_COM,unsigned char *buf,u16 len);
//���ڷ����ַ�������
void USART_SendString(USART_TypeDef *USART_COM,unsigned char *s);




















#endif


