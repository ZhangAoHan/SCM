
/*  UartDMA.h  */



#ifndef __UART_DMA_H_
#define __UART_DMA_H_

#include "sys.h"



/***********************************************************************/
//����DMA��������
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
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
//��ʼ������

//1����ʼ��uart
//2���رմ����ж�
//3������DMA_Uart_Init();

#endif






