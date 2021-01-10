/*---------------------------------------------------------
	      ����1 DMA�������ó���
	˵��: �������ó�����Ҫ����stdarg.h����ʹ��
	      �ܶ���ӿ�PA10->RXD  PA9->TXD,USART1
		  ʹ��printf��ʱ���\r\n��������س���
		  USART1�Ľ���DMAͨ��Ϊ5ͨ��,����DMAΪ4ͨ��
    ʱ��: 2014��1��22�� 
---------------------------------------------------------*/
#include "stm32f10x.h"
#include "usart1.h"
#include "misc.h"
#include "stdarg.h"
#include "oscilloscope.h"
#include "ucos_ii.h"
#include "pincfg.h"

#include "task_main.h"
#include "task_sd.h"
#include "task_gui.h"
#include "task_sd.h"
/*-----------------------------------------
		    	��������
------------------------------------------*/
extern WaveType WaveInfo;
extern WaveMode WaveCtrl;

unsigned char USART_Buffer[USART_BUFFER_SIZE];   //16�ֽڴ��ڻ�����
/*-----------------------------------------
 ��������: ���ô���1
------------------------------------------*/
void USART1_Config(void)
{
 	GPIO_InitTypeDef   IO_Init;
	USART_InitTypeDef  USART_InitStructure;
	DMA_InitTypeDef    DMA_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA , ENABLE);
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1, ENABLE);	//����DMAʱ��
	//A9�����������
	IO_Init.GPIO_Pin = GPIO_Pin_9;
	IO_Init.GPIO_Mode = GPIO_Mode_AF_PP;
	IO_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&IO_Init);
	
	//A10��������
	IO_Init.GPIO_Pin = GPIO_Pin_10;
	IO_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&IO_Init);
	
	USART_InitStructure.USART_BaudRate = 256000;  			    //���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//��λ����λ
	USART_InitStructure.USART_StopBits =  USART_StopBits_1;		//1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;			//��У��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ����
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	  //���͡�����ģʽ
	USART_Init(USART1,&USART_InitStructure);  	 //д������
	USART_Cmd(USART1,ENABLE);				     //ʹ�ܴ���
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); //ʹ�ܽ����ж�
	
	DMA_DeInit(DMA1_Channel5); 
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;	   
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)USART_Buffer;		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;		
    DMA_InitStructure.DMA_BufferSize = USART_BUFFER_SIZE;	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;		
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;  
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	   
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	DMA_Init(DMA1_Channel5,&DMA_InitStructure); 	   
	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);   //���ڽ���ʱʹ��DMA
	DMA_Cmd(DMA1_Channel5,ENABLE);				   //ʹ��DMA
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);	
}
/*---------------------------------------------------
 ��������: ����1 DMA��������жϷ���
 ����˵��: ÿ���յ�USART_BUFFER_SIZE���ֽڲ���1���ж�
           ���ж��н������ݲ��������Ӧ����,�ж����
		   ʱ�䣼1.5ms ���������ǰ�ѽ���ģ���������
		   �л��е�����Ӧ��λ�������ٶ���������.
---------------------------------------------------*/
void DMA1_Channel5_IRQHandler(void)
{
	OSIntNesting++;
	if(DMA_GetITStatus(DMA1_IT_TC5) == SET)	 
	{
		DMA_Cmd(DMA1_Channel5,DISABLE);	    //���������ر�DMA��ֹ���������ݱ�����			
		ReceiveDataFromPC();				//����PC����������
		DMA_ClearITPendingBit(DMA1_IT_TC5);
		DMA_Cmd(DMA1_Channel5,ENABLE);		//������ɴ�DMA		 
	}
	OSIntExit();	
}
/*------------------------------------------
 ��������: ����1�жϷ������(Ԥ��,����ɶҲû��)
------------------------------------------*/
void USART1_IRQHandler(void)
{
   OSIntNesting++;
   if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)  //����н����ж��һ�����û��
   {		
   		USART_ClearFlag(USART1,USART_IT_RXNE);  	   		   //����ж�λ
   } 
   OSIntExit();	
}


/* ʵ����printf�������ض������� */
int fputc(int ch,FILE *f)
{
 	USART_SendData(USART1, (unsigned char) ch);	//����stm32f10x_usart.c�еĺ���
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);  //�ȴ��������
	return ch;
}
/*---------------------------------------------------------
	��������: �Զ��������printf���ܺ���
	��������: ��Ҫ�������ݵĴ��ں�USARTx
			  ��Ҫ��ӡ������data
	���ز���: ��
---------------------------------------------------------*/
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
	int d;   
	char buf[16];
	
	va_list ap;
	va_start(ap, Data);
	
	while ( *Data != 0)     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
					USART_SendData(USARTx, 0x0d);
					Data ++;
				break;
				
				case 'n':							          //���з�
					USART_SendData(USARTx, 0x0a);	
					Data ++;
				break;
				
				default:
					Data ++;
				break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //�ַ���
					s = va_arg(ap, const char *);
					for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
					}
					Data++;
				break;
			
				case 'd':										//ʮ����
					d = va_arg(ap, int);
					itoa(d, buf, 10);
					for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
					}
					Data++;
				break;
			    default:  Data++;
				break;
			}		 
		} 
		else USART_SendData(USARTx, *Data++); //���û����ת���ַ����������
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
/*--------------------------------------------------
	��������: ��������ת�����ַ�������
	��������: ��Ҫת����������value
	          ת������ַ��� string
			  radix = 10
	��������: ��
---------------------------------------------------*/
static char *itoa(int value, char *string, int radix)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;
	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
	    *ptr = 0;
	    return string;
	}
	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}
	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
	    *ptr++ = '-';
	    /* Make the value positive. */
	    value *= -1;
	}
	for (i = 10000; i > 0; i /= 10)	//��ÿ������ÿһλ�ֱ��ʽ�����ַ�
	{
	    d = value / i;
	    if (d || flag)
	    {
	        *ptr++ = (char)(d + 0x30);
	        value -= (d * i);
	        flag = 1;
	    }
	}
	/* Null terminate the string. */
	*ptr = 0;
	return string;
}
