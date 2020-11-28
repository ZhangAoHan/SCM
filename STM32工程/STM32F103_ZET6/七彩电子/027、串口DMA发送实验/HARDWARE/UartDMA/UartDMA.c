
/*  UartDMA.c  */

#include "UartDMA.h"
#include "delay.h"



/***********************************************************************/
//����DMA��������
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/	 




uint8_t Usart_DMA_Tx_Busy_flag=0;


void USART_DMA_Rx_Init(uint8_t* rxBuf,uint32_t len){
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // ����DMA1ʱ��

	/*--- UART_Rx_DMA_Channel DMA Config ---*/
	
	DMA_Cmd(UART_Rx_DMA_Channel, DISABLE);                           // ��DMAͨ��  DMA1_Channel5   UART1_Rx_DMA_Channel
	DMA_DeInit(UART_Rx_DMA_Channel);                                 // �ָ�ȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DMA_RX_UART->DR);// ���ô��ڽ������ݼĴ���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)rxBuf;         // ���ý��ջ������׵�ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      // ��������Ϊ����Դ������Ĵ��� -> �ڴ滺����
	DMA_InitStructure.DMA_BufferSize = len;                     // ��Ҫ�����ܽ��յ����ֽ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // �����ַ�������ӵ�����������������DMA�Զ�ʵ�ֵ�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // �ڴ滺������ַ���ӵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // �������ݿ��8λ��1���ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // �ڴ����ݿ��8λ��1���ֽ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // ����ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // ���ȼ�����
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // �ر��ڴ浽�ڴ��DMAģʽ		
	DMA_Init(UART_Rx_DMA_Channel, &DMA_InitStructure);               // д������		
	DMA_ClearFlag(UART_Rx_DMA_FLAG);                                 // ���DMA���б�־		
	DMA_Cmd(UART_Rx_DMA_Channel, ENABLE);                            // ��������DMAͨ�����ȴ���������

	
	DMA_ITConfig(UART_Rx_DMA_Channel,DMA_IT_TC,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = UART_Rx_DMA_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_ITConfig(UART_Rx_DMA_Channel,DMA_IT_TC,ENABLE);
		
	USART_DMACmd(DMA_RX_UART, USART_DMAReq_Rx, ENABLE); // ��������DMA����
}



void USART_DMA_Tx_Init(void){
	
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // ����DMA1ʱ��
	
	/*---UART_Tx_DMA_Channel DMA Config ---*/

	DMA_Cmd(UART_Tx_DMA_Channel, DISABLE);                           // ��DMAͨ��
	DMA_DeInit(UART_Tx_DMA_Channel);                                 // �ָ�ȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DMA_TX_UART->DR);// ���ô��ڷ������ݼĴ���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)0;         // ���÷��ͻ������׵�ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                      // ��������λĿ�꣬�ڴ滺���� -> ����Ĵ���
	DMA_InitStructure.DMA_BufferSize = 0;                     // ��Ҫ���͵��ֽ�����������ʵ��������Ϊ0����Ϊ��ʵ��Ҫ���͵�ʱ�򣬻��������ô�ֵ
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // �����ַ�������ӵ�����������������DMA�Զ�ʵ�ֵ�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // �ڴ滺������ַ���ӵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // �������ݿ��8λ��1���ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // �ڴ����ݿ��8λ��1���ֽ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // ���δ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // ���ȼ�����
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // �ر��ڴ浽�ڴ��DMAģʽ
	DMA_Init(UART_Tx_DMA_Channel, &DMA_InitStructure);               // д������
	DMA_ClearFlag(UART_Tx_DMA_FLAG);                                 // ���DMA���б�־
	DMA_Cmd(UART_Tx_DMA_Channel, DISABLE); // �ر�DMA
	
	NVIC_InitStructure.NVIC_IRQChannel = UART_Tx_DMA_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	DMA_ITConfig(UART_Tx_DMA_Channel, DMA_IT_TC, ENABLE);            // ��������DMAͨ���ж�  

	USART_DMACmd(DMA_TX_UART,USART_DMAReq_Tx,ENABLE);

}

//
void Uart_DMA_Start_SendBuf(uint8_t *addr,uint16_t size) {
	u32 t=0;
	if(size<=0){
		return;
	}
	while(Usart_DMA_Tx_Busy_flag==1){//�ȴ���һ֡���ݷ������
		delay_ms(1);
		t++;
		if(t>200){//���200ms��û�з������,ǿ�ƽ���
			DMA_Cmd(DMA1_Channel4,DISABLE);
			DMA_ClearFlag(DMA1_FLAG_TC4);
			Usart_DMA_Tx_Busy_flag=0;
			break;
		}
	}
	Usart_DMA_Tx_Busy_flag=1;
	UART_Tx_DMA_Channel->CMAR=(uint32_t)addr;
	UART_Tx_DMA_Channel->CNDTR = (uint16_t)size; //����Ҫ���͵��ֽ���Ŀ     
	DMA_Cmd(UART_Tx_DMA_Channel, ENABLE);        //��ʼDMA����
}

//
uint8_t Get_Usart_DMA_Tx_Busy_Sta(void){
	return Usart_DMA_Tx_Busy_flag;
}
//����1DMA��ʽ�����ж�,
//�����󵥴ν������ݳ��ȴﵽ����ֵ֮�����������ж�,
void DMA1_Channel5_IRQHandler()
{
  if(DMA_GetITStatus(DMA1_IT_TC5)){
		
    DMA_ClearITPendingBit(DMA1_IT_TC5);
  }    
}

//����1DMA��ʽ�����ж�
void DMA1_Channel4_IRQHandler(void)
{
	//�����־λ
  	DMA_ClearFlag(DMA1_FLAG_TC4);
	//DMA_ClearITPendingBit(DMA1_FLAG_TC4);
  //DMA1->IFCR |= DMA1_FLAG_TC4;
	//�ر�DMA
	DMA_Cmd(DMA1_Channel4,DISABLE);
	Usart_DMA_Tx_Busy_flag=0;
 	//DMA1_Channel4->CCR &= ~(1<<0);
}
























