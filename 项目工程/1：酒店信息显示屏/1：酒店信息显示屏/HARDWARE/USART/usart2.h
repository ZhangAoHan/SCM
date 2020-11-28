#ifndef __USART2_H
#define __USART2_H
#include "sys.h"
#include "stdio.h"	 
#define USART_REC_LEN2  			200  
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF2[USART_REC_LEN2]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA2;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void usart2_init(u32 pclk2,u32 bound);
#endif	   
