
/*  UartDMA.c  */

#include "UartDMA.h"
#include "delay.h"



/***********************************************************************/
//串口DMA驱动代码
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/	 




uint8_t Usart_DMA_Tx_Busy_flag=0;


void USART_DMA_Rx_Init(uint8_t* rxBuf,uint32_t len){
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // 开启DMA1时钟

	/*--- UART_Rx_DMA_Channel DMA Config ---*/
	
	DMA_Cmd(UART_Rx_DMA_Channel, DISABLE);                           // 关DMA通道  DMA1_Channel5   UART1_Rx_DMA_Channel
	DMA_DeInit(UART_Rx_DMA_Channel);                                 // 恢复缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DMA_RX_UART->DR);// 设置串口接收数据寄存器
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)rxBuf;         // 设置接收缓冲区首地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      // 设置外设为数据源，外设寄存器 -> 内存缓冲区
	DMA_InitStructure.DMA_BufferSize = len;                     // 需要最大可能接收到的字节数
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // 外设地址不做增加调整，调整不调整是DMA自动实现的
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // 内存缓冲区地址增加调整
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度8位，1个字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // 内存数据宽度8位，1个字节
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // 传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // 优先级设置
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // 关闭内存到内存的DMA模式		
	DMA_Init(UART_Rx_DMA_Channel, &DMA_InitStructure);               // 写入配置		
	DMA_ClearFlag(UART_Rx_DMA_FLAG);                                 // 清除DMA所有标志		
	DMA_Cmd(UART_Rx_DMA_Channel, ENABLE);                            // 开启接收DMA通道，等待接收数据

	
	DMA_ITConfig(UART_Rx_DMA_Channel,DMA_IT_TC,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = UART_Rx_DMA_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_ITConfig(UART_Rx_DMA_Channel,DMA_IT_TC,ENABLE);
		
	USART_DMACmd(DMA_RX_UART, USART_DMAReq_Rx, ENABLE); // 开启串口DMA接收
}



void USART_DMA_Tx_Init(void){
	
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // 开启DMA1时钟
	
	/*---UART_Tx_DMA_Channel DMA Config ---*/

	DMA_Cmd(UART_Tx_DMA_Channel, DISABLE);                           // 关DMA通道
	DMA_DeInit(UART_Tx_DMA_Channel);                                 // 恢复缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DMA_TX_UART->DR);// 设置串口发送数据寄存器
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)0;         // 设置发送缓冲区首地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                      // 设置外设位目标，内存缓冲区 -> 外设寄存器
	DMA_InitStructure.DMA_BufferSize = 0;                     // 需要发送的字节数，这里其实可以设置为0，因为在实际要发送的时候，会重新设置次值
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // 外设地址不做增加调整，调整不调整是DMA自动实现的
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // 内存缓冲区地址增加调整
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度8位，1个字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // 内存数据宽度8位，1个字节
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // 单次传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // 优先级设置
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // 关闭内存到内存的DMA模式
	DMA_Init(UART_Tx_DMA_Channel, &DMA_InitStructure);               // 写入配置
	DMA_ClearFlag(UART_Tx_DMA_FLAG);                                 // 清除DMA所有标志
	DMA_Cmd(UART_Tx_DMA_Channel, DISABLE); // 关闭DMA
	
	NVIC_InitStructure.NVIC_IRQChannel = UART_Tx_DMA_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	DMA_ITConfig(UART_Tx_DMA_Channel, DMA_IT_TC, ENABLE);            // 开启发送DMA通道中断  

	USART_DMACmd(DMA_TX_UART,USART_DMAReq_Tx,ENABLE);

}

//
void Uart_DMA_Start_SendBuf(uint8_t *addr,uint16_t size) {
	u32 t=0;
	if(size<=0){
		return;
	}
	while(Usart_DMA_Tx_Busy_flag==1){//等待上一帧数据发送完毕
		delay_ms(1);
		t++;
		if(t>200){//如果200ms还没有发送完毕,强制结束
			DMA_Cmd(DMA1_Channel4,DISABLE);
			DMA_ClearFlag(DMA1_FLAG_TC4);
			Usart_DMA_Tx_Busy_flag=0;
			break;
		}
	}
	Usart_DMA_Tx_Busy_flag=1;
	UART_Tx_DMA_Channel->CMAR=(uint32_t)addr;
	UART_Tx_DMA_Channel->CNDTR = (uint16_t)size; //设置要发送的字节数目     
	DMA_Cmd(UART_Tx_DMA_Channel, ENABLE);        //开始DMA发送
}

//
uint8_t Get_Usart_DMA_Tx_Busy_Sta(void){
	return Usart_DMA_Tx_Busy_flag;
}
//串口1DMA方式接收中断,
//开启后单次接收数据长度达到设置值之后便会产生这个中断,
void DMA1_Channel5_IRQHandler()
{
  if(DMA_GetITStatus(DMA1_IT_TC5)){
		
    DMA_ClearITPendingBit(DMA1_IT_TC5);
  }    
}

//串口1DMA方式发送中断
void DMA1_Channel4_IRQHandler(void)
{
	//清除标志位
  	DMA_ClearFlag(DMA1_FLAG_TC4);
	//DMA_ClearITPendingBit(DMA1_FLAG_TC4);
  //DMA1->IFCR |= DMA1_FLAG_TC4;
	//关闭DMA
	DMA_Cmd(DMA1_Channel4,DISABLE);
	Usart_DMA_Tx_Busy_flag=0;
 	//DMA1_Channel4->CCR &= ~(1<<0);
}
























