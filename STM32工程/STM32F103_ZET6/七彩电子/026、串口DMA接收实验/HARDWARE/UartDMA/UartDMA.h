
/*  UartDMA.h  */



#ifndef __UART_DMA_H_
#define __UART_DMA_H_

#include "sys.h"



/***********************************************************************/
//串口DMA驱动代码
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/	 





#define DMA_TX_UART              USART1 
#define UART_Tx_DMA_Channel      DMA1_Channel4
#define UART_Tx_DMA_FLAG         DMA1_FLAG_GL4//DMA1_FLAG_TC2 | DMA1_FLAG_TE2 
#define UART_Tx_DMA_IRQ          DMA1_Channel4_IRQn


#define DMA_RX_UART              USART1 
#define UART_Rx_DMA_Channel      DMA1_Channel5
#define UART_Rx_DMA_FLAG         DMA1_FLAG_GL5//DMA1_FLAG_TC3 | DMA1_FLAG_TE3 
#define UART_Rx_DMA_IRQ          DMA1_Channel5_IRQn



extern uint8_t Usart_DMA_Tx_Busy_flag;




void USART_DMA_Rx_Init(uint8_t* rxBuf,uint32_t len);
void USART_DMA_Tx_Init(void);
void Uart_DMA_Start_SendBuf(uint8_t *addr,uint16_t size);
uint8_t Get_Usart_DMA_Tx_Busy_Sta(void);

	
	
	
//void DMA_Uart_Init(void);
//void Uart_Start_DMA_Tx(uint8_t *addr,uint16_t size);
//初始化步骤

//1、初始化uart
//2、关闭串口中断
//3、调用DMA_Uart_Init();

#endif






