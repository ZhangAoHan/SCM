#ifndef __USART_H_
#define __USART_H_


#include "stdio.h"
#include "sys.h"


/***********************************************************************/
//串口驱动程序(支持USART1 USART2 USART3 UART4 UART5)
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//移植注意，并不是所有的STM32F103芯片都支持5个串口
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/	 


void USART1_Init(u32 bound);//串口1初始化函数
void USART2_Init(u32 bound);//串口2初始化函数
void USART3_Init(u32 bound);//串口3初始化函数
void UART4_Init (u32 bound);//串口4初始化函数
void UART5_Init (u32 bound);//串口5初始化函数
//串口发送一个字节
void USART_SendByte(USART_TypeDef *USART_COM,u8 c);
//串口发送数组函数
void USART_SendBuf(USART_TypeDef *USART_COM,unsigned char *buf,u16 len);
//串口发送字符串函数
void USART_SendString(USART_TypeDef *USART_COM,unsigned char *s);




















#endif


