#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART1_RX_BUF[64],USART2_RX_BUF[64],USART3_RX_BUF[64]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8 USART1_RX_STA,USART2_RX_STA,USART3_RX_STA;         		//接收状态标记	
 
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 pclk2,u32 bound);
#define EN_USART2_RX    1//使能串口2接收
#define EN_USART3_RX    1//使能串口2接收
void uart2_init(u32 pclk2,u32 bound);
void uart3_init(u32 pclk2,u32 bound);
#endif	   
















